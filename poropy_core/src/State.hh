//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   State.hh
 *  @brief  State class definition.
 */
//---------------------------------------------------------------------------//


#ifndef POROPY_STATE_HH_
#define POROPY_STATE_HH_

#include <memory>
#include <vector>

#include "Definitions.hh"

namespace poropy
{

/**
 *  @class State
 *  @brief The current state of the core
 *
 *  The state captures a snapshot of the current
 *  reactor state.
 */
class State
{

public:

  State(const int number_assemblies);

  void set_keff(const double k);

  vec_dbl& assembly_power_peaking_factor();
  vec_dbl& fuel_temperature();
  vec_dbl& moderator_temperature();

private:

  double _keff;
  double _boron_concentration;
  double _cycle_length;
  vec_dbl _assembly_power_peaking_factor;
  vec_dbl _fuel_temperature;
  vec_dbl _moderator_temperature;
};

} // end namespace poropy

#endif /* POROPY_STATE_HH_ */
