//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   core_fixture.hh
 *  @brief  Build a core for testing
 */
//---------------------------------------------------------------------------//


#ifndef POROPY_TEST_CORE_FIXTURE_HH_
#define POROPY_TEST_CORE_FIXTURE_HH_

#include "Core.hh"

namespace poropy
{

Core::SP_core get_core()
{
  int s[9][9] =
      {{  0,  1,  2,  3,  4,  5,  6,  7, -1},
       { -2,  8,  9, 10, 11, 12, 13, 14, -1},
       { -2, 15, 16, 17, 18, 19, 20, 21, -1},
       { -2, 22, 23, 24, 25, 26, 27, 28, -1},
       { -2, 29, 30, 31, 32, 33, 34, -1, -1},
       { -2, 35, 36, 37, 38, 39, 40, -1, -1},
       { -2, 41, 42, 43, 44, 45, -1, -1, -1},
       { -2, 46, 47, 48, -1, -1, -1, -1, -1},
       { -1, -1, -1, -1, -1, -1, -1, -1, -1}
      };

  vec2_int stencil(9, vec_int(9));
  vec_size_t pattern(49, 0);
  for (int i = 0; i < 9; ++i)
  {
     for (int j = 0; j < 9; ++j)
      stencil[i][j] = s[i][j];
  }
  for (int i = 0; i < 49; ++i)
  {
    pattern[i] = i;
  }
  Core::SP_core core(new Core(stencil, 21.0));
  core->build();
  core->set_pattern(pattern);

  double bu[49] =
    {30.0, 15.0,  0.0, 30.0,  0.0, 15.0, 30.0, 30.0, 15.0, 30.0,  0.0, 15.0,
     15.0,  0.0, 30.0, 30.0,  0.0, 15.0, 15.0,  0.0,  0.0, 30.0,  0.0, 15.0,
     15.0, 15.0, 15.0,  0.0, 30.0, 15.0, 15.0, 15.0, 15.0,  0.0, 30.0, 15.0,
      0.0, 15.0,  0.0,  0.0, 30.0,  0.0,  0.0,  0.0, 30.0, 30.0, 30.0, 30.0,
      30.0};

  Core::vec_assembly assemblies;
  for (int i = 0; i < 49; ++i)
  {
    Assembly::SP_assembly a(new Assembly(i, 0, 0.5, bu[i]));
    assemblies.push_back(a);
  }

  core->set_assemblies(assemblies);

  return core;
}

} // end namespace poropy

#endif /* POROPY_TEST_CORE_FIXTURE_HH_ */
