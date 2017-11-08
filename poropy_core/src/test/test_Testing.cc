//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   test_Testing.cc
 *  @brief  Test of the simple Testing utilities.
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                \
        FUNC(test_Testing_pass)  \
        FUNC(test_Testing_fail)

#include "TestDriver.hh"

// System headers
#include <iostream>
#include <cstdlib>

using namespace poropy_test;
using namespace std;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

// Test definitions.

int test_Testing_pass(int argc, char *argv[])
{
 TEST(1==1);
 return 0;
}

int test_Testing_fail(int argc, char *argv[])
{
 TESTFALSE(1==0);
 return 0;
}

//---------------------------------------------------------------------------//
//              end of testTesting.cc
//---------------------------------------------------------------------------//
