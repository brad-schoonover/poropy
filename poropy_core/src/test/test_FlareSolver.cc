//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   test_FlareSolver.cc
 *  @brief  Test the FlareSolver class.
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                    \
        FUNC(test_FlareSolver)       \
	FUNC(test_FlareSolver_burnup)

#include <iostream>
#include <cstdlib>

#include "TestDriver.hh"

#include "FlareSolver.hh"
#include "FixedDataModel.hh"
#include "SimpleDataModel.hh"
#include "core_fixture.hh"

using namespace poropy;
using namespace poropy_test;
using namespace std;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

int test_FlareSolver(int argc, char *argv[])
{
  ParamDB::SP_db db(new ParamDB());
  db->put<double>("mixing_factor", 0.98);
  db->put<double>("albedo_one_side", 0.0);
  db->put<double>("albedo_two_side", 0.0);

  Core::SP_core core = get_core();

  std::vector<FlareData> data(1);
  data[0].kinf = 1.0;
  data[0].migration_area = 60.0;
  data[0].kappa_over_nu = 1.2e-11;
  FixedDataModel::SP_data_model model(new FixedDataModel(data));
  double power = 3.4;
  FlareSolver solver(db, core, model, power);
  solver.solve();
  return 0;
}


int test_FlareSolver_burnup(int argc, char *argv[])
{
  ParamDB::SP_db db(new ParamDB());
  db->put<double>("mixing_factor", 0.98);
  db->put<double>("albedo_one_side", 0.0);
  db->put<double>("albedo_two_side", 0.0);
  db->put<int>("burnup_option", FlareSolver::CYCLE_LENGTH);
  db->put<int>("critical_boron", 1);
  Core::SP_core core = get_core();
  SimpleDataModel::SP_data_model model(new SimpleDataModel());
  double power = 3.4;
  FlareSolver solver(db, core, model, power);
  vec_dbl burnup_steps {1.,1.,1.,1.,2.,2.,2.,2.,2.,2.,2.,2.,2.,2.,2.};
  vec_dbl T_F(49, 900);
  vec_dbl T_M(49, 580);
  solver.set_temperatures(T_F, T_M);
  solver.set_burnup_steps(burnup_steps);
  solver.solve();
  return 0;
}
