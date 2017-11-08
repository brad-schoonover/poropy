//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   FixedDataModel.hh
 *  @brief  FixedDataModel class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_FIXEDDATAMODEL_HH_
#define POROPY_FIXEDDATAMODEL_HH_

#include "BaseDataModel.hh"

namespace poropy
{

/**
 *  @class FixedDataModel
 *  @brief Allows users to defined data for a single state point
 */
class FixedDataModel: public BaseDataModel
{

public:

  FixedDataModel(const std::vector<FlareData> &data);

  FixedDataModel(const std::vector<TwoGroupData> &data);

  FixedDataModel(const vec_dbl &kinf,
		 const vec_dbl &m2,
		 const vec_dbl &kappa_over_nu);

  FixedDataModel(const vec_dbl &D1,
		 const vec_dbl &D2,
		 const vec_dbl &Sigma_f1,
		 const vec_dbl &Sigma_f2,
		 const vec_dbl &Sigma_a1,
		 const vec_dbl &Sigma_a2,
		 const vec_dbl &Sigma_s12,
		 const vec_dbl &nu_1,
		 const vec_dbl &nu_2,
		 const vec_dbl &kappa_1,
		 const vec_dbl &kappa_2);

  /// Compute assembly data for use in FLARE model
  virtual void update_data(Assembly::SP_assembly assembly,
                           const double     	 B,
                           const double     	 T_F,
                           const double     	 T_M,
                           const double     	 B_C,
                           FlareData       	&data);

  /// Compute assembly data for use in two-group models
  virtual void update_data(Assembly::SP_assembly assembly,
                           const double          B,
                           const double          T_F,
                           const double     	 T_M,
                           const double     	 B_C,
                           TwoGroupData    	&data);

private:

  /// Vector of FLARE data for multiple assembly types
  std::vector<FlareData> _flare_data;

  /// Vector of two-group data for multiple assembly types
  std::vector<TwoGroupData> _two_group_data;

};

} // end namespace poropy

#endif /* POROPY_FIXEDDATAMODEL_HH_ */
