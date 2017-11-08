//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseThermalModel.hh
 *  @brief  BaseThermalModel class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_BASETHERMALMODEL_HH_
#define POROPY_BASETHERMALMODEL_HH_

#include "Core.hh"

namespace poropy
{

class BaseThermalModel
{

public:

  /// Typedefs
  typedef std::shared_ptr<BaseThermalModel> SP_thermal_model;

  /**
   *  @brief Constructor
   *  @param 	db 	user parameter database
   *  @param 	core 	reactor core
   */
  BaseThermalModel(ParamDB::SP_db db, Core::SP_core core);

  /// Destructor
  virtual ~BaseThermalModel(){};

  /**
   *  @brief Computes volume-averaged assembly fuel and moderator temperatures
   *
   *  This default thermal model is extremely simple and is based on the
   *  following, potentially-limiting assumptions:
   *    + a single channel per assembly
   *    + a single, assembly-averaged specific heat (c_p)
   *    + a sinusoidal axial power shape
   *    + and so on.
   *
   *  @param 	assembly_powers		assembly powers (GW)
   *  @param	assembly_burnups	assembly burnups (GWd/MT)
   *  @param 	T_F			assembly fuel temperatures (K)
   *  @param 	T_M			assembly moderator temperatures (K)
   */
  virtual void compute_temperatures(const vec_dbl &assembly_powers,
                                    const vec_dbl &assembly_burnups,
                                    vec_dbl       &T_F,
                                    vec_dbl       &T_M);

protected:

  /// User parameter database
  ParamDB::SP_db _db;
  /// Reactor core
  Core::SP_core _core;

private:

  /// Specific heat, J/kg-K
  double _cp;
  /// Heat transfer coefficient, W/m^2-K
  double _h;
  /// Assembly mass flow rate, kg/s
  double _mdot;
  /// Inlet temperature, K
  double _T_inlet;

  /**
   *  Simplified correlation based on NFI correlation.
   *
   *  @param 	T_F 	Fuel temperature (K)
   *  @param  	B	  Burnup (GWd/MT)
   */
  double fuel_conductivity(double T_F, double B);

  /**
   *  Returns thermal conductivity (W/m) for Zr-4 at temperature T (K)
   *
   *  Valid for 300K <= T <= 1800K.
   *  Originally from MATPRO.
   *
   *  @param 	T_C     cladding average temperature (K)
   */
  double cladding_conductivity(const double T_C);

  /**
   *  Simple gap conductance model based on Figure 8.24 of Todreas and Kazimi.
   *
   *  @param 	B       burnup (GWd/MT)
   */
  double gap_conductance(const double B);

};

} // end namespace poropy

#endif /* POROPY_BASETHERMALMODEL_HH_ */
