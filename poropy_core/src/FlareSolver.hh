//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   FlareSolver.hh
 *  @brief  FlareSolver class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_FLARESOLVER_HH_
#define POROPY_FLARESOLVER_HH_

#include "BaseSolver.hh"

namespace poropy
{

/**
 *  @class FlareSolver
 *  @brief Implementation of a 2-D, FLARE-like nodal method
 *
 *  The FLARE method was developed in the early 1960's for BWR analysis.  Its
 *  simplicity makes it a nice option for very simple scoping studies.
 */
class FlareSolver: public BaseSolver
{

public:

  FlareSolver(ParamDB::SP_db          db,
              Core::SP_core           core,
              BaseDataModel::SP_data_model model,
              const double            power);

private:

  /// Compute the power distribution for a fixed, single state
  virtual void solve_single_state();

  /// flare model parameters
  double _mixing_factor;
  double _albedo_one_side;
  double _albedo_two_side;

  /// solver convergence criteria
  double _tol_keff;
  double _tol_s;
  size_t _max_inners;
  size_t _max_outers;

  /// flare coefficients
  vec_dbl _wpp;
  vec_dbl _wqp;
  vec_dbl _wleak;

  // flare material parameters
  vec_dbl _kinf;
  vec_dbl _M2;
  vec_dbl _kappa_over_nu;

  /// Implementation
  void build_coefficients();

};

} // end namespace poropy

#endif /* POROPY_FLARESOLVER_HH_ */
