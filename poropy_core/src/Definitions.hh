//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Definitions.hh
 *  @brief  Useful type definitions, etc.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_DEFINITIONS_HH_
#define POROPY_DEFINITIONS_HH_

#include <vector>
#include <map>

namespace poropy
{

typedef unsigned int size_t;
typedef unsigned int u_int;

typedef std::vector<int> vec_int;
typedef std::vector<std::vector<int> > vec2_int;
typedef std::vector<std::vector<std::vector<int> > > vec3_int;

typedef std::vector<double> vec_dbl;
typedef std::vector<std::vector<double> > vec2_dbl;
typedef std::vector<std::vector<std::vector<double> > > vec3_dbl;

typedef std::vector<size_t> vec_size_t;
typedef std::vector<std::vector<size_t> > vec2_size_t;
typedef std::vector<std::vector<std::vector<size_t> > > vec3_size_t;

} // end namespace poropy

#endif // POROPY_DEFINITIONS_HH_
