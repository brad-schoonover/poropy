//----------------------------------*-C++-*----------------------------------//
/**
 *  @file  test_ParamDB.cc
 *  @brief Test of ParamDB
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                    \
        FUNC(test_ParamDB)

#include "TestDriver.hh"
#include "ParamDB.hh"
#include "SoftEquivalence.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace poropy_test;
using namespace poropy;
using namespace std;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

// Test definitions.

int test_ParamDB(int argc, char *argv[])
{
 ParamDB::SP_db db(new ParamDB());

 // Check that when we insert, it shows up, and we can get it.

 // int
 db->put<int>("number_groups", 2);
 TEST(db->check("number_groups"));
 int ng = db->get<int>("number_groups");
 TEST(ng == 2);

 // double
 db->put<double>("inner_tolerance", 0.0001);
 TEST(db->check("inner_tolerance"));
 double tol = db->get<double>("inner_tolerance");
 TEST(soft_equiv(tol, 0.0001));

 // vecint
 vec_int vint(10, 1);
 db->put<vec_int>("vector_of_ints", vint);
 TEST(db->check("vector_of_ints"));
 vec_int vint2 = db->get<vec_int>("vector_of_ints");
 TEST(vint2.size() == 10);
 for (int i = 0; i < 10; i++)
 {
   TEST(vint[i] == vint2[i]);
 }

 // vecdbl
 vec_dbl vdbl(10, 1.0);
 db->put<vec_dbl>("vector_of_dbls", vdbl);
 TEST(db->check("vector_of_dbls"));
 vec_dbl vdbl2 = db->get<vec_dbl>("vector_of_dbls");
 TEST(vdbl2.size() == 10);
 for (int i = 0; i < 10; i++)
 {
   TEST(soft_equiv(vdbl[i], vdbl2[i]));
 }

 // string
 db->put<string>("equation", "dd");
 TEST(db->check("equation"));
 string eq = db->get<string>("equation");
 TEST(eq=="dd");

 // input db
 ParamDB::SP_db db2(new ParamDB("DB2"));
 db2->put<int>("testint", 99);
 db2->put<double>("testdbl", 1.23);
 db->put<ParamDB::SP_db>("db2", db2);
 TEST(db->check("db2"));
 ParamDB::SP_db db2check;
 db2check = db->get<ParamDB::SP_db>("db2");
 TEST(db2check.get()!=0);
 int testint = db2check->get<int>("testint");
 TEST(testint == 99);
 double testdbl = db2check->get<double>("testdbl");
 TEST(soft_equiv(testdbl, 1.23));

 // Test that something is not there.
 TEST(!db->check("i_am_not_here"));

 return 0;
}
