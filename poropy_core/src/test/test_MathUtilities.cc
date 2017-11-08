//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   test_Core.cc
 *  @brief  Test the the Core class.
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                         \
        FUNC(test_MathUtilities_vec_sum)  \
        FUNC(test_MathUtilities_vec_norm) \
        FUNC(test_MathUtilities_vec_residual_norm)


#include <iostream>
#include <cstdlib>

#include "TestDriver.hh"
#include "MathUtilities.hh"
#include "SoftEquivalence.hh"

using namespace poropy;
using namespace poropy_test;
using namespace std;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

// Test definitions.

int test_MathUtilities_vec_sum(int argc, char *argv[])
{
  vec_dbl v(10, 1.0);
  TEST(soft_equiv(vec_sum(v), 10.0));
  vec_int y(10, 1);
  TEST(vec_sum(y) == 10);
  return 0;
}

int test_MathUtilities_vec_norm(int argc, char *argv[])
{
  vec_dbl v(10, 1.0);
  TEST(soft_equiv(vec_norm(v), 3.16227766016838));
  return 0;
}

int test_MathUtilities_vec_residual_norm(int argc, char *argv[])
{
  vec_dbl v(10, 1.0);
  vec_dbl y(10, 1.1);
  TEST(soft_equiv(vec_residual_norm(v, y), 0.316227766016838));
  return 0;
}
