//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   SimpleDataModel.hh
 *  @brief  SimpleDataModel class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_SIMPLEDATAMODEL_HH_
#define POROPY_SIMPLEDATAMODEL_HH_

#include "BaseDataModel.hh"

namespace poropy
{

/**
 *  @class SimpleDataModel
 *  @brief Simple models for a typical 17x17 PWR assembly
 *
 *  Presently, only one configuration is implemented.  Various
 *  types will be added.
 */
class SimpleDataModel: public BaseDataModel
{

public:

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

  double kinf(const double B,
	      const double T_F,
	      const double T_M,
	      const double B_C);

  double migration_area(const double B,
			const double T_F,
			const double T_M,
			const double B_C);

  double kappa_over_nu(const double B,
		       const double T_F,
		       const double T_M,
		       const double B_C);

private:

};

} // end namespace poropy


#endif /* POROPY_SIMPLEDATAMODEL_HH_ */
