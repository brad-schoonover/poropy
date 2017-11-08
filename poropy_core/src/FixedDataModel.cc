//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   FixedDataModel.cc
 *  @brief  FixedDataModel class member definitions.
 */
//---------------------------------------------------------------------------//

#include "FixedDataModel.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
FixedDataModel::FixedDataModel(const std::vector<FlareData>& data)
  : _flare_data(data)
{
  Require(_flare_data.size() > 0);
}

//---------------------------------------------------------------------------//
FixedDataModel::FixedDataModel(const vec_dbl &kinf,
			       const vec_dbl &m2,
			       const vec_dbl &kappa_over_nu)
{
  Require(kinf.size() == m2.size());
  Require(kinf.size() == kappa_over_nu.size());
  _flare_data.resize(kinf.size());
  for (size_t i = 0; i < _flare_data.size(); ++i)
  {
    _flare_data[i].kinf = kinf[i];
    _flare_data[i].migration_area = m2[i];
    _flare_data[i].kappa_over_nu = kappa_over_nu[i];
  }
}

//---------------------------------------------------------------------------//
FixedDataModel::FixedDataModel(const std::vector<TwoGroupData>& data)
  : _two_group_data(data)
{
  Require(_two_group_data.size() > 0);
}

//---------------------------------------------------------------------------//
FixedDataModel::FixedDataModel(const vec_dbl &D1,
			       const vec_dbl &D2,
			       const vec_dbl &Sigma_f1,
			       const vec_dbl &Sigma_f2,
			       const vec_dbl &Sigma_a1,
			       const vec_dbl &Sigma_a2,
			       const vec_dbl &Sigma_s12,
			       const vec_dbl &nu_1,
			       const vec_dbl &nu_2,
			       const vec_dbl &kappa_1,
			       const vec_dbl &kappa_2)
{
  Require(D1.size() == D2.size());
  Require(D1.size() == Sigma_f1.size());
  Require(D1.size() == Sigma_f2.size());
  Require(D1.size() == Sigma_a1.size());
  Require(D1.size() == Sigma_a2.size());
  Require(D1.size() == Sigma_s12.size());
  Require(D1.size() == nu_1.size());
  Require(D1.size() == nu_2.size());
  Require(D1.size() == kappa_1.size());
  Require(D1.size() == kappa_2.size());

  _flare_data.resize(D1.size());
  for (size_t i = 0; i < _flare_data.size(); ++i)
  {
    _flare_data[i].kinf =
	(nu_1[i]*Sigma_f1[i] + nu_2[i]*Sigma_f2[i]*Sigma_s12[i]/Sigma_a2[i]) /
	  (Sigma_a1[i] + Sigma_s12[i]);
    _flare_data[i].migration_area =
	D1[i]/(Sigma_a1[i]+Sigma_s12[i]) + D2[i]/Sigma_a2[i];
    // if the fluxes were added as parameters, use a flux-weighted kappa
    _flare_data[i].kappa_over_nu = kappa_1[i];
  }

  _two_group_data.resize(D1.size());
  for (size_t i = 0; i < _two_group_data.size(); ++i)
  {
    _two_group_data[i].D1 = D1[i];
    _two_group_data[i].D2 = D1[i];
    _two_group_data[i].Sigma_f1 = Sigma_f1[i];
    _two_group_data[i].Sigma_f2 = Sigma_f2[i];
    _two_group_data[i].Sigma_a1 = Sigma_a1[i];
    _two_group_data[i].Sigma_a2 = Sigma_a2[i];
    _two_group_data[i].Sigma_s12 = Sigma_s12[i];
    _two_group_data[i].nu_1 = nu_1[i];
    _two_group_data[i].nu_2 = nu_2[i];
    _two_group_data[i].kappa_1 = kappa_1[i];
    _two_group_data[i].kappa_2 = kappa_2[i];
  }
}

//---------------------------------------------------------------------------//
void FixedDataModel::update_data(Assembly::SP_assembly assembly,
                                 const double     B,
                                 const double     T_F,
                                 const double     T_M,
                                 const double     B_C,
                                 FlareData       &data)
{
  Require(assembly.get() != 0);
  Require(assembly->type() < _flare_data.size());
  data =_flare_data[assembly->type()];
}

//---------------------------------------------------------------------------//
void FixedDataModel::update_data(Assembly::SP_assembly assembly,
                                 const double     B,
                                 const double     T_F,
                                 const double     T_M,
                                 const double     B_C,
                                 TwoGroupData    &data)
{
  Require(assembly.get() != 0);
  Require(assembly->type() < _two_group_data.size());
  data =_two_group_data[assembly->type()];
}

} // end namespace poropy
