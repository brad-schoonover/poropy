//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   State.cc
 *  @brief  State class member definition.
 */
//---------------------------------------------------------------------------//

#include "State.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
State::State(const int number_assemblies)
  : _keff(1.0)
  , _boron_concentration(0.0)
  , _cycle_length(0.0),
  , _assembly_power_peaking_factor(number_assemblies, 1.0)
  , _fuel_temperature(number_assemblies, 900.0)
  , _moderator_temperature(number_assemblies, 580.0)
{

}

} // end namespace poropy
