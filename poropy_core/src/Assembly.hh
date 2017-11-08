//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Assembly.hh
 *  @brief  Assembly class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_ASSEMBLY_HH_
#define POROPY_ASSEMBLY_HH_

#include "ParamDB.hh"

#include <memory>

namespace poropy
{

/**
 *  @class Assembly
 *  @brief Represents a reactor assembly
 */
class Assembly
{

public:

  /// Typedefs
  typedef std::shared_ptr<Assembly> SP_assembly;

  /**
   *  @param serial_number      integer identifying the specific assembly
   *  @param type               integer identifying type of assembly
   *  @param mass               (initial) heavy metal mass (MTU)
   *  @param burnup             boc assembly burnup (GWd/MTU)
   *  @param db                 optional parameter database
   */
  Assembly(const size_t    serial_number,
           const size_t    type,
           const double    mass,
           const double    burnup,
           ParamDB::SP_db  db = NULL);

  size_t serial_number() const {return _serial_number;}
  size_t type() const {return _type;}
  double mass() const {return _mass;}
  double burnup() const {return _burnup;}

  size_t number_pins() const {return _number_pins;}
  double fuel_radius() const {return _r_f;}
  double cladding_inner_radius() const {return _r_ci;}
  double cladding_outer_radius() const {return _r_co;}

  ParamDB::SP_db db() const {return _db;}

  /// Update the assembly burnup
  void set_burnup(const double b);


  /// Reset the assembly burnup to BOC value
  void reset_burnup();

  /// Set the fuel dimensions
  void set_fuel_dimensions(const double r_f,
                           const double r_ci,
                           const double r_co);

  Assembly()
    : _serial_number(0), _type(0), _mass(0), _burnup(0), _burnup_boc(0)
  {}

private:

  /// Unique number used to identify the assembly
  size_t _serial_number;
  /// Number used to identify type of fuel
  size_t _type;
  /// Heavy metal mass (MTU)
  double _mass;
  /// Burnup (GWd/MTU)
  double _burnup;
  /// BOC burnup (GWd/MTU)
  double _burnup_boc;

  /// Fuel radius (cm)
  double _r_f;
  /// Cladding inner radius (cm)
  double _r_ci;
  /// Cladding outer radius (cm)
  double _r_co;
  /// Number of fuel pins
  size_t _number_pins;

  /// Parameter database for other assembly options
  ParamDB::SP_db _db;
};

}

#endif /* POROPY_ASSEMBLY_HH_ */
