//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   Core.cc
 *  @brief  Core class member definitions.
 */
//---------------------------------------------------------------------------//

#include "Core.hh"
#include "DBC.hh"
#include "Definitions.hh"

#include <iostream>
#include <cstdio>

namespace poropy
{

//---------------------------------------------------------------------------//
Core::Core(const vec2_int stencil,
           const double   width,
           const double   height)
  : _stencil(stencil)
  , _width(width)
  , _height(height)
  , _number_assemblies(0)
{
  Require(_width > 0.0);
  Require(_height > 0.0);
}

//---------------------------------------------------------------------------//
void Core::build()
{
  // Go through the stencil once and record dimensions
  size_t n = _stencil[0].size();
  vec_size_t number_per_row(n, 0);
  vec_size_t number_per_col(n, 0);
  size_t k = 0;
  for (size_t i = 0; i < n; ++i)
  {
     for (size_t j = 0; j < n; ++j)
     {
       if (_stencil[i][j] >= 0)
       {
         // set initial pattern to stencil values
         _pattern.push_back((size_t)_stencil[i][j]);
         // stencil will now hold cardinal location index
         _stencil[i][j] = k;
         number_per_row[i] += 1;
         number_per_col[j] += 1;
         ++k;
       }
     }
  }
  _number_assemblies = _pattern.size();

  // subtract the first element, since we handle it explicitly below
  //number_per_row[0] -= 1;

  // for each bundle, record the neighbors
  _neighbors.resize(_number_assemblies, vec_int(4, -1));
  // central bundle is always adjacent to bundle 1
  for (int i = 0; i < 4; ++i)
    _neighbors[0][i] = 1;
  // do other nodes
  k = 1;
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      // skip the first element and non fuel locations
      if ((i > 0 or j > 0) and _stencil[i][j] >= 0)
      {
        // west
        if (j > 1)
          _neighbors[k][0] = _stencil[i][j-1];
        else
          _neighbors[k][0] = _stencil[0][i  ];    // rotational
        // east
        if (j < number_per_row[i])
          _neighbors[k][1] = _stencil[i][j+1];
        else
          _neighbors[k][1] = -1;                  // reflector
        // bottom
        if (i < number_per_col[j])
          _neighbors[k][2] = _stencil[i+1][j];
        else
          _neighbors[k][2] = -1;                  // reflector
        // top
        if (i > 0)
          _neighbors[k][3] = _stencil[i-1][j];
        else
          _neighbors[k][3] = _stencil[j  ][1];    // rotational
        ++k;
      }
    }
  }
  Assert(k == _number_assemblies);

  _number_neighbors.resize(_number_assemblies, 0);
  for (size_t i = 0; i < _number_assemblies; ++i)
  {
     k = 0;
     for (size_t j = 0; j < 4; ++j)
     {
         if (_neighbors[i][j] >= 0) ++k;
     }
     _number_neighbors[i] = k;
  }

//  for (size_t i = 0; i < _number_assemblies; ++i)
//  {
//    std::cout << " assembly " << i << " -- ";
//    for (size_t j = 0; j < 4; ++j)
//    {
//      std::cout << " " << neighbor(i, j);
//    }
//    std::cout << std::endl;
//  }
  Ensure(_number_assemblies > 0);
}

//---------------------------------------------------------------------------//
void Core::add_assembly(Assembly::SP_assembly a)
{
  Require(a.get() != 0);
  _assemblies.push_back(a);
  Ensure(_assemblies.size() <= _number_assemblies);
}

//---------------------------------------------------------------------------//
void Core::set_assemblies(vec_assembly a)
{
  Require(a.size() == _number_assemblies);
#ifdef POROPY_ENABLE_DBC
  for (size_t i = 0; i < _number_assemblies; ++i)
  {
    Require(a[i].get() != 0);
  }
#endif
  _assemblies = a;
}

//---------------------------------------------------------------------------//
void Core::set_pattern(const vec_size_t &p)
{
  Require(p.size() == _number_assemblies);
#ifdef POROPY_ENABLE_DBC
  for (size_t i = 0; i < _number_assemblies; ++i)
  {
    Require(p[i] < _number_assemblies);
  }
#endif
  _pattern = p;
}

//---------------------------------------------------------------------------//
int Core::number_neighbors(const size_t a) const
{
  Require(a < _number_assemblies);
  return _number_neighbors[a];
}

//---------------------------------------------------------------------------//
int Core::pattern(const size_t i)
{
  Require(i < _number_assemblies);
  return _pattern[i];
}

//---------------------------------------------------------------------------//
Assembly::SP_assembly Core::assembly(const size_t i)
{
  Require(i < _number_assemblies);
  return _assemblies[i];
}


//---------------------------------------------------------------------------//
void Core::print_assembly_map(const vec_dbl &v, std::string name)
{
  Require(v.size() == _number_assemblies);
  std::cout << "***" << name << std::endl;
  size_t k = 0;
  for (size_t i = 0; i < _stencil.size(); ++i)
  {
    for (size_t j = 0; j < _stencil[i].size(); ++j)
    {
      if (_stencil[i][j] >= 0)
      {
        std::printf(" %9.4f", v[k]);
        ++k;
      }
      else
      {
        std::printf("          ");
      }
    }
    std::printf("\n");
  }
}

} // end namespace poropy
