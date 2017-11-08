//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   SoftEquivalence.hh
 *  @brief  Soft_Equivalence functions for floating point comparisons.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_SOFTEQUIVALENCE_HH
#define POROPY_SOFTEQUIVALENCE_HH

#include "DBC.hh"

#include <algorithm>
#include <cmath>

namespace poropy
{

/**
 * @brief Compare two scalars for equivalence within a given tolerance.
 * @param v 	scalar value to compare
 * @param r 	scalar value against which value is compared
 * @param p  	tolerance of relative error
 * @return 	true if values are the equivalent within the tolerance
 *              false otherwise
 */
template <class T>
inline bool soft_equiv(const T &v,
                       const T &r,
		       const T  p = 1.0e-12)
{
  // check absolute difference, which handles small-p case
  if (std::fabs(v - r) < p)
    return true;
  // check relative difference
  if(std::fabs(v - r) < std::max(std::fabs(v), std::fabs(r)) * p)
    return true;
  return false;
}

} // end namespace poropy

#endif // POROPY_SOFTEQUIVALENCE_HH
