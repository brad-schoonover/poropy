//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   FlareSolver.cc
 *  @brief  FlareSolver class member definitions.
 */
//---------------------------------------------------------------------------//

#include "FlareSolver.hh"
#include "DBC.hh"
#include "MathUtilities.hh"

#include <cmath>
#include <iostream>
#include <cstring>
namespace poropy
{

//---------------------------------------------------------------------------//
FlareSolver::FlareSolver(ParamDB::SP_db          db,
                         Core::SP_core           core,
                         BaseDataModel::SP_data_model model,
                         const double            power)
  : BaseSolver(db, core, model, power)
  , _mixing_factor(0.9885)
  , _albedo_one_side(-0.138)
  , _albedo_two_side(-0.004)
  , _tol_keff(1.0e-5)
  , _tol_s(1.0e-5)
  , _max_inners(10)
  , _max_outers(100)
  , _wpp(_core->number_assemblies(), 0.0)
  , _wqp(_core->number_assemblies(), 0.0)
  , _wleak(_core->number_assemblies(), 0.0)
  , _kinf(_core->number_assemblies(), 0.0)
  , _M2(_core->number_assemblies(), 0.0)
  , _kappa_over_nu(_core->number_assemblies(), 0.0)
{
  if (_db->check("mixing_factor"))
    _mixing_factor = _db->get<double>("mixing_factor");
  if (_db->check("albedo_one_side"))
    _albedo_one_side = _db->get<double>("albedo_one_side");
  if (_db->check("albedo_two_side"))
    _albedo_two_side = _db->get<double>("albedo_two_side");
}

//---------------------------------------------------------------------------//
void FlareSolver::solve_single_state()
{
  size_t n = _core->number_assemblies();

  // Initialize the fission source
  vec_dbl s(n, 1.0/n);

  // Guess k = 1
  double keff = 1.0;

  // Update coefficients
  build_coefficients();

  double err_keff = 0.0;
  double err_s = 0.0;

  // temporary outer and inner source vectors
  vec_dbl s_o(s.size(), 0.0);
  vec_dbl s_i(s.size(), 0.0);

  // outer iteration
  size_t outer;
  for (outer = 0; outer < _max_outers; ++outer)
  {
    s_o = s;

    // inner iteration -- helps avoid premature convergence
    for (size_t inner = 0; inner < _max_inners; ++inner)
    {
      s_i = s;
      for (size_t p = 0; p < n; ++p)
      {
        s[p] = _wpp[p] * s_i[p];
        for (size_t q = 0; q < 4; ++q)
        {
          int qq = _core->neighbor(p, q);
          if (qq >= 0)
          {
            s[p] = s[p] + _wqp[qq] * s_i[qq];
          }
        }
        s[p] = s[p] * _kinf[p] / keff;
      }
    } // end inner

    // normalize the source
    vec_scale(s, 1.0/vec_sum(s));

    // Update k
    double k_o = keff;
    double k_num = 0.0;
    double k_den = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
      k_num = k_num + s[i]*_wleak[i];
      k_den = k_den + s[i]/_kinf[i];
    }
    keff = (vec_sum(s) - k_num) / k_den;

    // Update errors and check for convergence
    err_keff = abs(keff - k_o);
    err_s = vec_residual_norm(s, s_o);
    if  (err_keff < _tol_keff && err_s < _tol_s)
    {
      break;
    }
  } // end outer

  // set the eigenvalue
  _keff = keff;

  // compute the assembly powers
  for (size_t i = 0; i < _core->number_assemblies(); ++i)
    _assembly_powers[i] = s[i] * _kappa_over_nu[i];
  scale_assembly_powers(_assembly_powers);
}

//---------------------------------------------------------------------------//
void FlareSolver::build_coefficients()
{
  // Update kinf, M2, and kappa/nu.  These arrays are ordered consistent with
  // the geometric layout of the core, *not* the order of the assemblies as
  // stored in the core assembly array.
  FlareData data;
  for (size_t i = 0; i < _core->number_assemblies(); ++i)
  {
    int id = _core->pattern(i);

    _data_model->update_data(_core->assembly(id),
                        _B[i], _TF[i], _TM[i], _BC, data);
    _kinf[i] = data.kinf;
    _M2[i] = data.migration_area;
    _kappa_over_nu[i] = data.kappa_over_nu;
  }

  // Now, compute the coefficients, wpp and wqp.
  double width = _core->width();
  double g1 = 0.5 * (1.0 - _mixing_factor) / width;
  double g2 = _mixing_factor / (width * width);
  double aI  = 1.0 - _albedo_one_side;
  double aII = 1.0 - _albedo_two_side;

  for (size_t i = 0; i < _core->number_assemblies(); ++i)
  {
    // Compute a single probability
    double w = g1 * std::sqrt(_M2[i]) + g2 * _M2[i];

    // Subtract leakage to actual neigbors
    _wpp[i] = 1.0 - _core->number_neighbors(i) * w;
    // Build coefficients
    if (_core->number_neighbors(i) == 3)
    {
      // account for one external surface
      _wleak[i] = w * aI;
      _wpp[i]   = _wpp[i] - _wleak[i];
    }
    else if (_core->number_neighbors(i) == 2)
    {
      // account for two external surfaces
      _wleak[i] = 2.0 * w * aII;
      _wpp[i]   = _wpp[i] - _wleak[i];
    }
    else if (_core->number_neighbors(i) == 4)
    {
      // I'm internal and there is no leakage
      _wleak[i]  = 0.0;
    }
    else
    {
      THROW("number of neighbors is off!!");
    }
    // My leakage to another
    _wqp[i] = w;
  }

//  for (int i=0; i < 49; ++i)
//  {
//    std::printf("%4i %12.8f %12.8f %12.8f\n", i, _wpp[i], _wqp[i], _wleak[i]);
//  }

}

} // end namespace poropy
