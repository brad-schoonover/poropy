//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseSolver.hh
 *  @brief  BaseSolver class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_BASESOLVER_HH_
#define POROPY_BASESOLVER_HH_

#include "Core.hh"
#include "Definitions.hh"
#include "BaseDataModel.hh"
#include "ParamDB.hh"
#include "BaseThermalModel.hh"

#include <memory>

namespace poropy
{

/**
 *  @class BaseSolver
 *  @brief Abstract neutronics solver class for 2-D PWR analysis
 *
 *  The purpose of this class is to extract the parts common to any
 *  (simple) neutronics scheme, e.g., thermal-hydraulic feedback
 *  calculations, critical boron search, and burnup steps.
 *
 *  What remains is the major task: solving for the core power distribution,
 *  which is left as a pure virtual function to be implemented by the
 *  user.
 */
class BaseSolver
{

public:

  /// Enumerations
  enum BURNUP_OPTION
  {
    NO_BURNUP,
    FIXED_STEPS,
    CYCLE_LENGTH,
    END_BURNUP_OPTION
  };

  /// Typedefs
  typedef std::shared_ptr<BaseSolver> SP_solver;

  /**
   *  @brief Constructor
   *  @param    db 	    Parameter database
   *  @param    core 	  Core
   *  @param    model	  Material data model
   *  @param    power 	Core power (GWth)
   */
  BaseSolver(ParamDB::SP_db          db,
             Core::SP_core           core,
             BaseDataModel::SP_data_model model,
             const double            power);

  /// Destructor
  virtual ~BaseSolver(){}

  /// Find the power distribution, accounting for boron, TH, and depletion.
  void solve();

  /// Sets user-defined burnup steps (in GWd/MTU)
  void set_burnup_steps(const vec_dbl &steps);

  /// Sets user-defined temperatures
  void set_temperatures(const vec_dbl &T_F, const vec_dbl &T_M);

  /// Set thermal model
  void set_thermal_model(BaseThermalModel::SP_thermal_model th_model);

  /// Getters
  //@{
  double keff() const {return _keff;}
  vec_dbl assembly_powers() const {return _assembly_powers;}
  vec_dbl fuel_temperature() const {return _TF;}
  vec_dbl moderator_temperature() const {return _TM;}
  vec_dbl cycle_keff() const {return _cycle_keff;}
  vec_dbl cycle_boron() const {return _cycle_boron;}
  vec_dbl cycle_max_appf() const {return _cycle_max_appf;}
  vec_dbl cycle_core_burnup() const {return _cycle_core_burnup;}
  //@}

protected:

  /// Parameter database
  ParamDB::SP_db _db;
  /// Reactor core
  Core::SP_core _core;
  /// Assembly material data model
  BaseDataModel::SP_data_model _data_model;
  /// Thermal-hydraulics model
  BaseThermalModel::SP_thermal_model _thermal_model;

  /// RUN OPTIONS
  //@{

  /// Are we doing a critical boron search?
  bool _critical_boron;
  /// Maximum boron iterations at a step
  size_t _max_boron_iters;
  /// Are we including thermal-hydraulic feedback?
  bool _thermal_hydraulics;
  /// Maximum TH iterations at a step
  size_t _max_thermal_iters;

  /**
   *  @brief Burnup option, 0=none, 1=fixed steps, 2=cycle length
   *
   *  With the fixed-step option, the user steps are used directly, and
   *  the final core is general not critical.  With the cycle-length option,
   *  the user steps are used used until the estimated step to critical
   *  is smaller than the user step.  The search for critical is done
   *  for up to the number of steps remaining in the user vector.
   */
  size_t _burnup_option;

  //@}

  /// CORE PROPERTIES
  //@{

  /// Assembly burnups (GWd/MT)
  vec_dbl _B;
  /// Assembly fuel temperatures (K)
  vec_dbl _TF;
  /// Assembly moderator temperatures (K)
  vec_dbl _TM;
  /// Assembly powers (GW)
  vec_dbl _assembly_powers;
  /// Core boron concentration (ppm)
  double _BC;
  /// Eigenvalue
  double _keff;
  /// Core power (GWth)
  double _power;
  /// Average assembly power (GWth)
  double _average_assembly_power;
  /// Core mass (MTU)
  double _mass;
  /// Specific power (GW/MTU)
  double _power_per_mass;

  //@}

  /// DEPLETION PARAMETERS
  //@{

  /// User-defined burnup steps (in GWd/MTU)
  vec_dbl _burnup_steps;
  /// Number of burnup steps (= length of user-defined vector)
  size_t _number_burnup_steps;
  /// Eigenvalue that defines criticality (> 1 to account for axial leakage)
  double _critical_keff;
  /// Tolerance on end-of-cycle eigenvalue
  double _keff_tol_cycle;

  /// Core burnup as a function of step
  vec_dbl _cycle_core_burnup;
  /// Eigenvalue at each burnup step
  vec_dbl _cycle_keff;
  /// Boron concentration at each step
  vec_dbl _cycle_boron;
  /// Maximimum assembly power peaking factor at each step
  vec_dbl _cycle_max_appf;

  //@}

  /// Scale a given assembly power vector to the core power
  void scale_assembly_powers(vec_dbl &ap);

private:

  /**
   *  @brief Find the power distribution given fixed material properties
   *
   *  Concrete implementations of BaseSolver must implement this.  The only
   *  requirement is that method updates (1) the eigenvalue and (2) the
   *  assembly powers.
   */
  virtual void solve_single_state() = 0;

  /**
   *  @brief Solve for the steady state core conditions
   *
   *  This solves the coupled neutronics and thermal-hydraulics
   *  equations assuming a very simple, assembly-averaged temperature
   *  model.
   */
  void solve_steady_state();

  /**
   *  @brief Solve for the critical cycle length
   *
   *  This determines the critical cycle length of a given fuel loading.
   *  Thermal-hydraulic feedback and/or a critical boron search can be
   *  included.
   */
  void solve_cycle();

  /// Critical boron search
  void compute_critical_boron();

  /**
   *  @brief Compute assembly temperatures
   *
   *  For given assembly relative powers, assembly dimensions, and
   *  total core power, etc., compute the assembly temperatures.
   */
  void compute_assembly_temperatures();

  /**
   *  @brief Estimate the burnup step that would lead to criticality
   *
   *  @param b0 	old burnup
   *  @param b1         new burnup
   *  @param x0         old core parameter (e.g., keff or boron concentration)
   *  @param x1         new core parameter
   *  @oaram xc         critical value of parameter (e.g., keff = 1 or bc = 0)
   *  @return           burnup that yields xc
   */
  double critical_step(const double b0, const double b1,
                       const double x0, const double x1,
                       const double xc) const;

  /// Pretty print the top of the cycle data points
  void print_burnup_header() const;

  /// Pretty print a cycle data point
  void print_burnup(size_t i, double bu, double fpd,
                    double mappf_c, double mappf_s, double keff,
                    double bc, double cl) const;
};

} // end namespace poropy

#endif /* POROPY_BASESOLVER_HH_ */
