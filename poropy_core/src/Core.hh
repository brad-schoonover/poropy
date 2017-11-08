//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Core.hh
 *  @brief  Core class definition.
 */
//---------------------------------------------------------------------------//


#ifndef POROPY_CORE_HH_
#define POROPY_CORE_HH_

#include <memory>
#include <vector>

#include "Assembly.hh"
#include "Definitions.hh"

namespace poropy
{

/**
 *  @class Core
 *  @brief Represents a reactor core
 *
 *  The problem geometry is defined by a "stencil" that specifies
 *  where fuel exists, where reflector exists, and where
 *  void exists.  Only quarter cores can be modeled.
 *
 *  An example stencil for a small core is
 *
 *        [[ 0,  1,  2,  3,  4, -1],
 *          -2,  5,  6,  7,  8, -1],
 *          -2,  9, 10, 11, 12, -1],
 *          -2, 13, 14, 15, -1, -1],
 *          -2, 16, 17, -1, -1, -1],
 *          -1, -1, -1, -1, -1, -1]]
 *
 *  Fuel is indicated by a non-negative value, void by -1, and
 *  locations defined by symmetry with -2's.  The initial values
 *  in the fueled region are used as the initial pattern, though
 *  the user can update the pattern.
 *
 *  The core pattern is an integer array that maps each fuel assembly
 *  in the assembly vector to a physical location in the stencil.  The
 *  lay out is exactly as illustrated in the core stencil above, i.e.,
 *  the central assembly is first.
 */
class Core
{

public:

  // Typedefs
  typedef std::shared_ptr<Core> SP_core;
  typedef std::vector<Assembly::SP_assembly> vec_assembly;

  Core(const vec2_int stencil,
       const double   width,
       const double   height = 366.0);

  /// Build the geometry
  void build();
  /// Set assembly
  void add_assembly(Assembly::SP_assembly a);
  /// Set the assemblies
  void set_assemblies(vec_assembly a);
  /// Set the core pattern
  void set_pattern(const vec_size_t &p);
  /// Return the number of neighbors of an assembly
  int number_neighbors(const size_t a) const;
  /// Return the nth neighbor of an assembly. -1 indicates void.
  inline int neighbor(const size_t a, const size_t n) const;
  /// Return the assembly width
  double width() const {return _width;}
  /// Return the active fuel height
  double height() const {return _height;}
  /// Return the number of assemblies in the core
  size_t number_assemblies() const {return _number_assemblies;}
  /// Return id
  int pattern(const size_t i);
  vec_size_t pattern() const {return _pattern;}

  Assembly::SP_assembly assembly(const size_t i);

  /// Print a map of assembly-wise values
  void print_assembly_map(const vec_dbl &v, std::string name);

private:

  /// 2-D core layout.  Non-zero = fuel, -1 void, and -2 symmetry.
  vec2_int _stencil;
  /// Specifies where each
  vec_size_t _pattern;
  double _width;
  double _height;
  vec_assembly _assemblies;
  vec2_int _neighbors;
  size_t _number_assemblies;
  vec_size_t _number_neighbors;
};

} // end namespace poropy

//---------------------------------------------------------------------------//
// INLINE MEMBER DEFINITIONS
//---------------------------------------------------------------------------//

#include "Core.i.hh"

#endif /* POROPY_CORE_HH_ */
