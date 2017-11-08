//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   MathUtilities.hh
 *  @brief  Utilities for vector math operations
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_MATHUTILITIES_HH_
#define POROPY_MATHUTILITIES_HH_

#include "Definitions.hh"

#include <algorithm>
#include <cmath>
#include <limits>

namespace poropy
{

/// L-2 norm of a vector
template <class T>
inline double vec_norm(const std::vector<T> &v)
{
  T f = 0;
  for (size_t i = 0; i < v.size(); ++i)
    f += v[i]*v[i];
  return std::sqrt((double)f);
}

/// L-2 norm of the residual of two vectors.
template <class T>
inline double vec_residual_norm(std::vector<T> &x, std::vector<T> &y)
{
  Require(x.size() == y.size());
  T v = 0.0;
  for (size_t i = 0; i < x.size(); ++i)
  {
    T z = x[i]-y[i];
    v += z*z;
  }
  return std::sqrt((double)v);
}

/// Reset a vector
template <class T>
inline void vec_set(std::vector<T> &x, T value)
{
  for (size_t i = 0; i < x.size(); ++i)
    x[i] =  value;
}

/// Scale a vector
template <class T>
inline void vec_scale(std::vector<T> &x, T scale)
{
  for (size_t i = 0; i < x.size(); ++i)
    x[i] = x[i] * scale;
}

/// Return the minimum of a vector.
template <class T>
inline T vec_min(const std::vector<T> &v)
{
  T m = std::numeric_limits<T>::max();
  for (size_t i = 0; i < v.size(); ++i)
    if (v[i] < m) m = v[i];
  return m;
}

/// Return the maximum of a vector.
template <class T>
inline T vec_max(const std::vector<T> &v)
{
  T m = std::numeric_limits<T>::min();
  for (size_t i = 0; i < v.size(); ++i)
    if (v[i] > m) m = v[i];
  return m;
}

/// Return the sum of a vector.
template <class T>
inline T vec_sum(const std::vector<T> &v)
{
  T s = 0;
  for (size_t i = 0; i < v.size(); ++i)
    s += v[i];
  return s;
}

} // end namespace poropy

#endif /* POROPY_MATHUTILITIES_HH_ */
