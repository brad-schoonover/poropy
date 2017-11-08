//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   SimpleDataModel.cc
 *  @brief  SimpleDataModel class member definition.
 */
//---------------------------------------------------------------------------//

#include "SimpleDataModel.hh"
#include "GenException.hh"

#include <cmath>

namespace poropy
{

//---------------------------------------------------------------------------//
void SimpleDataModel::update_data(Assembly::SP_assembly assembly,
				  const double     B,
				  const double     T_F,
				  const double     T_M,
				  const double     B_C,
				  FlareData       &data)
{
  data.kinf = kinf(B, T_F, T_M, B_C);
  data.migration_area = migration_area(B, T_F, T_M, B_C);
  data.kappa_over_nu = kappa_over_nu(B, T_F, T_M, B_C);
}

//---------------------------------------------------------------------------//
void SimpleDataModel::update_data(Assembly::SP_assembly assembly,
				  const double     B,
				  const double     T_F,
				  const double     T_M,
				  const double     B_C,
				  TwoGroupData    &data)
{
  THROW("Simple data model has no two-group support.")
}

//---------------------------------------------------------------------------//
double SimpleDataModel::kinf(const double B,
			     const double T_F,
			     const double T_M,
			     const double B_C)
{
  double rho = 0.265730719228072 +
	       0.017246243714514*std::atan2(0.0270156720657697, B) -
	       2.64328429981567e-5*T_F -
	       5.86741982668666e-5*B_C -
	       0.00144062296270426*B -
	       4.79134781011598e-7*B*B_C -
	       8.76211743462825e-6*B*T_M;
  return 1.0 / (1.0 - rho);
}

//---------------------------------------------------------------------------//
double SimpleDataModel::migration_area(const double B,
				       const double T_F,
				       const double T_M,
				       const double B_C)
{
  return 1.41350127802683*T_M +
         0.00112134680090497*B*B +
	 (397008.794613071 - 0.696210782691167*B_C)/T_M -
	 1439.98856519259 -
	 0.000249491110525838*B*T_M;
}

//---------------------------------------------------------------------------//
double SimpleDataModel::kappa_over_nu(const double B,
				      const double T_F,
				      const double T_M,
				      const double B_C)
{
  return 1.17456695915967e-11 +
         1.01076308347919e-8 /
	   (11154.4037184315 + 0.0655884891875816*B_C +
	    B*T_M + 0.0116673460208095*B*B_C -
            6.48231256151913e-6*std::exp(0.399979646507731*B)) -
         1.07610322931692e-14*B;
}

} // end namespace poropy
