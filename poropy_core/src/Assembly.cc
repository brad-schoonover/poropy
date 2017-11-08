//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Assembly.cc
 *  @brief  Assembly class member definitions.
 */
//---------------------------------------------------------------------------//

#include "poropy_config.h"
#include "Assembly.hh"
#include "DBC.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
Assembly::Assembly(const size_t   serial_number,
                   const size_t   type,
                   const double   mass,
                   const double   burnup,
                   ParamDB::SP_db db)
  : _serial_number(serial_number)
  , _type(type)
  , _mass(mass)
  , _burnup(burnup)
  , _burnup_boc(burnup)
  , _r_f(0.4096)
  , _r_ci(0.4180)
  , _r_co(0.4750)
  , _number_pins(264)
  , _db(db)
{
  Require(_burnup >= 0.0);
}

//---------------------------------------------------------------------------//
void Assembly::set_burnup(const double b)
{
  Require(b > _burnup_boc);
  _burnup = b;
}

//---------------------------------------------------------------------------//
void Assembly::set_fuel_dimensions(const double r_f,
                                   const double r_ci,
                                   const double r_co)
{
  Require(r_f > 0.0);
  Require(r_ci > r_f);
  Require(r_co > r_ci);
  _r_f = r_f;
  _r_ci = r_ci;
  _r_co = r_co;
}

//---------------------------------------------------------------------------//
void Assembly::reset_burnup()
{
 _burnup = _burnup_boc;
}

} // end namespace poropy
