//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseDataModel.hh
 *  @brief  BaseDataModel class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_BASEDATAMODEL_HH_
#define POROPY_BASEDATAMODEL_HH_

#include "Assembly.hh"
#include "ParamDB.hh"

namespace poropy
{

/// Data needed for FLARE
struct FlareData
{
  double kinf;
  double migration_area;
  double kappa_over_nu;
};

/// Data needed for two-group solvers
struct TwoGroupData
{
  double D1;
  double D2;
  double Sigma_f1;
  double Sigma_f2;
  double Sigma_a1;
  double Sigma_a2;
  double Sigma_s12;
  double nu_1;
  double nu_2;
  double kappa_1;
  double kappa_2;
};

/**
 *  @class BaseDataModel
 *  @brief Abstract class for defining assembly material properties
 *
 *  Data models
 */
class BaseDataModel
{

public:

  /// Typedefs
  typedef std::shared_ptr<BaseDataModel> SP_data_model;

  BaseDataModel(ParamDB::SP_db db = NULL);

  virtual ~BaseDataModel() = 0;

  /**
   *  @brief Compute assembly data for use in FLARE model
   *  @param assembly 	the assembly to be updated
   *  @param B		burnup (GWd/MTU)
   *  @param T_F	fuel temperature (K)
   *  @param T_M 	moderator temperature (K)
   *  @param B_C	core boron concentration (ppm)
   *  @param data       FLARE data to be updated
   */
  virtual void update_data(Assembly::SP_assembly assembly,
                           const double     	 B,
                           const double     	 T_F,
                           const double     	 T_M,
                           const double     	 B_C,
                           FlareData       	&data) = 0;

  /**
   *  @brief Compute assembly data for use in two-group models
   *  @param assembly 	the assembly to be updated
   *  @param B		burnup (GWd/MTU)
   *  @param T_F	fuel temperature (K)
   *  @param T_M 	moderator temperature (K)
   *  @param B_C	core boron concentration (ppm)
   *  @param data       two-group data to be updated
   */
  virtual void update_data(Assembly::SP_assembly  assembly,
                           const double     B,
                           const double     T_F,
                           const double     T_M,
                           const double     B_C,
                           TwoGroupData    &data) = 0;

protected:

  /// User parameter database
  ParamDB::SP_db _db;

};

} // end namespace poropy

#endif /* POROPY_BASEDATAMODEL_HH_ */
