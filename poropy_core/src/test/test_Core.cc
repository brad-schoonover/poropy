//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   test_Core.cc
 *  @brief  Test the Core class.
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                \
        FUNC(test_Core)

#include <iostream>
#include <cstdlib>

#include "TestDriver.hh"

#include "core_fixture.hh"

using namespace poropy;
using namespace poropy_test;
using namespace std;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

// Test definitions.

int test_Core(int argc, char *argv[])
{
  Core::SP_core core = get_core();

  TEST(core->number_neighbors(0) == 4)
  TEST(core->neighbor(0, 0) == 1);

  vec_dbl stuff(core->number_assemblies(), 1.23);

  core->print_assembly_map(stuff, "stuff");

  return 0;
}
