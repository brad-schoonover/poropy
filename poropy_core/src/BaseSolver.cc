//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseSolver.cc
 *  @brief  BaseSolver class member definitions.
 */
//---------------------------------------------------------------------------//

#include "BaseSolver.hh"
#include "MathUtilities.hh"
#include "SoftEquivalence.hh"
#include "BaseThermalModel.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
BaseSolver::BaseSolver(ParamDB::SP_db          db,
                       Core::SP_core           core,
                       BaseDataModel::SP_data_model model,
                       const double            power)
  : _db(db)
  , _core(core)
  , _data_model(model)
//
  , _critical_boron(false)
  , _max_boron_iters(10)
  , _thermal_hydraulics(false)
  , _max_thermal_iters(10)
  , _burnup_option(NO_BURNUP)
//
  , _BC(0.0)
  , _keff(0.0)
  , _power(power)
  , _average_assembly_power(0.0)
  , _mass(0.0)
  , _power_per_mass(0.0)
//
  , _number_burnup_steps(0)
  , _critical_keff(1.04)
  , _keff_tol_cycle(1.0e-5)
{
  Require(_db.get()!=0);
  Require(_core.get()!=0);
  Require(_data_model.get()!=0);
  Require(_power > 0.0);

  if (_db->check("critical_boron"))
  {
    _critical_boron = _db->get<int>("critical_boron")==1;
  }

  if (_db->check("thermal_hydraulics"))
  {
    _thermal_hydraulics = _db->get<int>("thermal_hydraulics")==1;
    if (_db->check("max_thermal_iters"))
    {
      _max_thermal_iters = _db->get<int>("max_thermal_iters");
    }
  }

  if (_db->check("burnup_option"))
  {
    _burnup_option = _db->get<int>("burnup_option");
    Require(_burnup_option < END_BURNUP_OPTION);
  }

  _B.resize(_core->number_assemblies(), 0.0);
  _TF.resize(_core->number_assemblies(), 900.0);
  _TM.resize(_core->number_assemblies(), 580.0);

  _assembly_powers.resize(_core->number_assemblies());

  // only one-quarter of the central assembly is counted
  _average_assembly_power = 0.25 * _power /
                            (_core->number_assemblies() - 0.75);

  _mass = _core->assembly(0)->mass();
  for (size_t i = 1; i < _core->number_assemblies(); ++i)
    _mass += 4.0 * _core->assembly(i)->mass();

  _power_per_mass = _power / _mass;

  // Update the local burnup vector with the assembly BOC burnups
  for (size_t i = 0; i < _core->number_assemblies(); ++i)
  {
    _B[i] = _core->assembly(_core->pattern(i))->burnup();
  }
}

//---------------------------------------------------------------------------//
void BaseSolver::solve()
{
  solve_steady_state();
  if (_burnup_option > NO_BURNUP)
  {
    solve_cycle();
  }
}

//---------------------------------------------------------------------------//
void BaseSolver::solve_steady_state()
{
  solve_single_state();

  if (_critical_boron)
    compute_critical_boron();

  if (_thermal_hydraulics)
  {
    // define base thermal model if none is currently defined
    if (_thermal_model.get() == 0)
    {
      _thermal_model = std::make_shared<BaseThermalModel>(_db, _core);
    }
    vec_dbl TF_old = _TF;
    for (size_t i = 0; i < _max_thermal_iters; ++i)
    {
      _thermal_model->compute_temperatures(_assembly_powers, _B, _TF, _TM);
      solve_single_state();
      if (_critical_boron)
        compute_critical_boron();
      double err = vec_residual_norm(_TF, TF_old);
      if (err < 1.0)
        break;
      TF_old = _TF;
    }
  }
}

//---------------------------------------------------------------------------//
void BaseSolver::solve_cycle()
{
  // just get the power distribution and escape if not burning
  if (_number_burnup_steps == 0) return;

  double fpd = 0.0;
  double burnup = 0.0;
  double burnup1 = 0.0;
  double keff1 = 0.0;
  double BC1 = 0.0;
  double burnup_step = 0.0;
  double cycle_length = 0.0;
  double mappf = 0.0;
  double mappf_cycle = 0.0;
  double mappf_bu = 0.0;

  _cycle_core_burnup.resize(_number_burnup_steps+1, 0.0);
  _cycle_keff.resize(_number_burnup_steps+1, 0.0);
  _cycle_boron.resize(_number_burnup_steps+1, 0.0);
  _cycle_max_appf.resize(_number_burnup_steps+1, 0.0);

  _cycle_keff[0] = _keff;
  _cycle_boron[0] = _BC;
  vec_dbl appf = _assembly_powers;
  vec_scale(appf, 1.0 / _average_assembly_power);
  mappf = vec_max(appf);
  _cycle_max_appf[0] = mappf;

  print_burnup_header();
  print_burnup(0, burnup, fpd, mappf, mappf, _keff, _BC, cycle_length);

  bool is_done = false;
  size_t step;
  for (step = 1; step <= _number_burnup_steps; ++step)
  {
    // determine the burnup step to take
    burnup_step = _burnup_steps[step-1];
    if (step > 2)
    {
      double crit_step;
      if (_critical_boron)
        crit_step = critical_step(burnup1, burnup, BC1, _BC, 0.0);
      else
        crit_step = critical_step(burnup1, burnup, keff1, _keff, _critical_keff);
      // estimated cycle length
      cycle_length = crit_step + burnup;
      // never take a step bigger than the user-defined step
      if (_burnup_option == CYCLE_LENGTH)
      {
        if (crit_step < burnup_step && crit_step > 0.0)
        {
          burnup_step = crit_step;
        }
      }
    }

    // record old values and update new ones
    burnup1 = burnup;
    keff1 = _keff;
    BC1 = _BC;
    burnup = burnup + burnup_step;
    double fpd_step = burnup_step * _mass / _power;
    fpd = fpd + fpd_step;

    // update assembly burnups
    for (size_t i = 0; i < _core->number_assemblies(); ++i)
    {
      size_t id = _core->pattern(i);
      _B[i] += _assembly_powers[i] * fpd_step / _core->assembly(id)->mass();
    }

    // solve the system at new burnup
    solve_steady_state();

    appf = _assembly_powers;
    vec_scale(appf, 1.0 / _average_assembly_power);
    mappf = vec_max(appf);
    _cycle_max_appf[step] = mappf;
    _cycle_keff[step] = _keff;
    _cycle_boron[step] = _BC;
    _cycle_core_burnup[step] = burnup;

    if (mappf > mappf_cycle)
    {
      mappf_cycle = mappf;
      mappf_bu    = burnup;
    }

    print_burnup(step, burnup, fpd, mappf_cycle, mappf, _keff, _BC, cycle_length);

    is_done = std::abs(_keff - _critical_keff) < 1e-5;
    if (_critical_boron)
      is_done = std::abs(_BC) < 1e-1;
    if (_burnup_option == CYCLE_LENGTH && is_done)
    {
      ++step;
      break;
    }
  }
  if (not is_done)
  {
    std::cout << "warning: cycle length not converged!" << std::endl;
  }

  appf = _assembly_powers;
  vec_scale(appf, 1.0 / _average_assembly_power);
  _core->print_assembly_map(appf, "assembly power peaking factors");
  _core->print_assembly_map(_B, "assembly burnups");

  _cycle_keff.resize(step);
  _cycle_core_burnup.resize(step);
  _cycle_max_appf.resize(step);
  _cycle_boron.resize(step);
}

//---------------------------------------------------------------------------//
void BaseSolver::set_temperatures(const vec_dbl &T_F, const vec_dbl &T_M)
{
  Require(T_F.size() == _core->number_assemblies());
  Require(T_M.size() == T_F.size());
  _TF = T_F;
  _TM = T_M;
}

//---------------------------------------------------------------------------//
void BaseSolver::set_burnup_steps(const vec_dbl &steps)
{
  if (steps.size() > 0)
  {
    for (size_t i = 0; i < steps.size(); ++i)
    {
      Require(steps[i] >= 0.0);
    }
  }
  _number_burnup_steps = steps.size();
  _burnup_steps = steps;
}

//---------------------------------------------------------------------------//
void BaseSolver::set_thermal_model(BaseThermalModel::SP_thermal_model thmodel)
{
  Require(thmodel.get() != 0);
  _thermal_model = thmodel;
}

//===========================================================================//
// IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
void BaseSolver::compute_critical_boron()
{
  // the critical boron search is done within any th-feedback iteration
  double keff1 = 0;
  double BC1 = 0;
  double slope = -1.0e-4;

  for (size_t i = 0; i < _max_boron_iters; ++i)
  {
    // save current values
    keff1 = _keff;
    BC1 = _BC;
    // 1.0 = slope * (BC_crit - BC) + keff
    // --> (1 - keff)/slope + BC = B_crit
    _BC = (_critical_keff-_keff)/slope + _BC;
    // update keff
    solve_single_state();
    // update slope
    slope = (_keff-keff1)/(_BC-BC1);
    // check for convergence
    if (std::abs(_keff-_critical_keff) < 1.0e-5)
    {
      break;
    }
    else if(soft_equiv(_keff, keff1))
    {
      std::cout << "warning -- keff did not change -- no boron dependence?"
	              << std::endl;
      break;
    }
  }
}

//---------------------------------------------------------------------------//
void BaseSolver::compute_assembly_temperatures()
{

}

//---------------------------------------------------------------------------//
void BaseSolver::scale_assembly_powers(vec_dbl &ap)
{
  vec_scale(_assembly_powers,
            0.25*_power/(vec_sum(_assembly_powers)-0.75*_assembly_powers[0]));
}

//---------------------------------------------------------------------------//
double BaseSolver::critical_step(const double b0, const double b1,
				 const double x0, const double x1,
				 const double xcrit) const
{
  // assume   x(b) = slope * (b-b0) + x0
  // then     xcrit = slope (bcrit -b0) + x0
  // or       (xcrit - x0)/slope + b0 = brit
  // finally  crit step = bcrit - b1
  double slope = (x1-x0)/(b1-b0);
  double step = (xcrit - x1)/slope;
  if (step < 0.0)
    step = 0.0;
  return step;
}

//---------------------------------------------------------------------------//
void BaseSolver::print_burnup_header() const
{
  using std::printf;
  if (_burnup_option == 0)
  {
    printf(" *** BURNUP CALCULATION WITH USER-SPECIFED BURNUP STEPS ***\n");
  }
  else if (_burnup_option == 1)
  {
    printf(" *** BURNUP CALCULATION FOR DETERMINATION OF CYCLE LENGTH ***\n");
  }
  printf("\n");
  printf("   ------------------------------------------------------------------------------------\n");
  printf("    STEP   BURNUP      FPD      MAX APPF   MAX APPF     KEFF     BORON      APPX.CYC.L \n");
  printf("          [GWd/MTU]   [day]      [cycle]    [step]               [ppm]      [GWd/MTU]  \n");
  printf("   ------------------------------------------------------------------------------------\n");
}

//---------------------------------------------------------------------------//
void BaseSolver::print_burnup(size_t i, double bu, double fpd,
			      double mappf_c, double mappf_s, double keff,
			      double bc, double cl) const
{
  std::printf("   %3i %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",
	      i, bu, fpd, mappf_c, mappf_s, keff, bc, cl);
  if (i == _number_burnup_steps)
  {
    std::printf("   -----------------------------------");
    std::printf("------------------------------------------------\n\n");
  }
}

} // end namespace poropy
