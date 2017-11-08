//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseThermalModel.cc
 *  @brief  BaseThermalModel class member definitions.
 */
//---------------------------------------------------------------------------//

#include <cmath>
#define _USE_MATH_DEFINES

#include "BaseThermalModel.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
BaseThermalModel::BaseThermalModel(ParamDB::SP_db db, Core::SP_core core)
  : _db(db)
  , _core(core)
  , _cp(5500.0)
  , _h(30000.0)
  , _mdot(88.0)
  , _T_inlet(563.0)
{
  Require(_db.get()!=0);
  Require(_core.get()!=0);
}

//---------------------------------------------------------------------------//
void BaseThermalModel::compute_temperatures(const vec_dbl &powers,
                                            const vec_dbl &burnups,
                                            vec_dbl       &T_F,
                                            vec_dbl       &T_M)
{
  // active height, m
  double height = _core->height() / 100.0;
  for (size_t i = 0; i < _core->number_assemblies(); ++i)
  {
    double B = burnups[i];

    // assembly index
    size_t p = _core->pattern(i);

    // fuel, inner/outer cladding, and effective gap radii
    double r_f  = _core->assembly(p)->fuel_radius()/100;
    double r_ci = _core->assembly(p)->cladding_inner_radius()/100;
    double r_co = _core->assembly(p)->cladding_outer_radius()/100;
    double r_g  = 0.5*(r_ci+r_f);

    // average linear heat generation rate, W/m
    double qp_avg = 1.e9*powers[i]/height;

    // axial-averaged moderator temperature
    T_M[i] = _T_inlet + 0.5*qp_avg*height/(_mdot*_cp);

    // cladding average temperate (K) and thermal conductivity W/m.K
    double T_C = 0.88*T_M[i] + 0.12*T_F[i];
    double k_C = cladding_conductivity(T_C);
    // gap conductance, W/m^2.K
    double h_g = gap_conductance(B);

    // effective non-fuel thermal conductivity, W/m.K
    double k_NF = 2*M_PI/(1.0/h_g/r_g + std::log(r_co/r_ci)/k_C + 1./r_co/_h);
    // fuel thermal conductivity, W/m.K
    double k_F = fuel_conductivity(T_F[i], B);

    // average pin linear heat generation rate, W/m
    double qp_pin = qp_avg / (double)_core->assembly(p)->number_pins();

    // axially- and radially-averaged fuel temperature
    T_F[i] = qp_pin*(0.125/M_PI/k_F + 1.0/k_NF) + T_M[i];
  }
}

//---------------------------------------------------------------------------//
double BaseThermalModel::fuel_conductivity(const double T_F, const double B)
{
  return 0.0118340600386467*B +
         2.10223405878539e-14*T_F*T_F*T_F*T_F +
         3923.09098668336/(154.72261735884 + T_F + 20.8225739516707*B) -
         2.03748805095159e-6*T_F*B - 4.19053096725081e-5*B*B;
}

//---------------------------------------------------------------------------//
double BaseThermalModel::cladding_conductivity(const double T_C)
{
  return 7.511 + 2.088e-2*T_C - 1.45e-5*T_C*T_C + 7.668e-9*T_C*T_C*T_C;
}

//---------------------------------------------------------------------------//
double BaseThermalModel::gap_conductance(const double B)
{
  double h = 0.6 + 0.5*B/30;
  if (B >= 30.0)
    h = 1.1;
  return h * 10000.0;
}

} // end namespace poropy
