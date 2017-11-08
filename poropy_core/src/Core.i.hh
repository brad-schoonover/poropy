//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Core.hh
 *  @brief  Core class inline member definitions.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_CORE_I_HH_
#define POROPY_CORE_I_HH_

namespace poropy
{

//---------------------------------------------------------------------------//
inline int Core::neighbor(const size_t a, const size_t n) const
{
  Require(a < _number_assemblies);
  Require(n < 4);
  return _neighbors[a][n];
}

} // end namespace poropy


#endif /* POROPY_CORE_I_HH_ */
