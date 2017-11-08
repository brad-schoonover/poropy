//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   poropy.i
 *  @brief  Python interface for Poropy core features.
 */
//---------------------------------------------------------------------------//

%module(directors="1") poropy_core
%{
#include <stddef.h>
#include "Definitions.hh"
#include "ParamDB.hh"
#include "Assembly.hh"
#include "Core.hh"
#include "BaseDataModel.hh"
#include "SimpleDataModel.hh"
#include "FixedDataModel.hh"
#include "BaseThermalModel.hh"
#include "BaseSolver.hh"
#include "FlareSolver.hh"
%} // end module poropy_core

// Somewhat nicely-formatted documentation from C++ source
%feature("autodoc", "3");

%include "poropy_config.h"

// STL
%include "std_string.i"
%include "std_vector.i"

// Smart pointers can be included as follows:
//   %shared_ptr(Base)
//   %shared_ptr(Derived<int>)
//   %shared_ptr(Derived<double>)
// Any shared_ptr(Foo) declaration *must* come before inclusion of Foo.hh.  
// In addition, any Base class must be declared before its derivative classes.
#define SWIG_SHARED_PTR_NAMESPACE std
%include <boost_shared_ptr.i>

// generate directors for all classes that have virtual methods
%feature("director");         

// STD Vectors
%include "Definitions.hh"
namespace std
{
  %template(vec_int)      vector<int>;
  %template(vec2_int)     vector<vector<int> >;
  %template(vec3_int)     vector<vector<vector<int> > >;
  %template(vec_dbl)      vector<double>;
  %template(vec2_dbl)     vector<vector<double> >;
  %template(vec3_dbl)     vector<vector<vector<double> > >;
  %template(vec_size_t)   vector<unsigned int>;
  %template(vec2_size_t)  vector<vector<unsigned int> >;
  %template(vec3_size_t)  vector<vector<vector<unsigned int> > >;
}

// Parameter database
%shared_ptr(poropy::ParamDB)
%include "ParamDB.hh"
namespace poropy
{
%template(get_int)      ParamDB::get<int>;
%template(get_dbl)      ParamDB::get<double>;
%template(get_vec_int)  ParamDB::get<vec_int>;
%template(get_vec_dbl)  ParamDB::get<vec_dbl>;
%template(get_str)      ParamDB::get<std::string>;
%template(get_spdb)     ParamDB::get<ParamDB::SP_db>;
%template(put_int)      ParamDB::put<int>;
%template(put_dbl)      ParamDB::put<double>;
%template(put_vec_int)  ParamDB::put<vec_int>;
%template(put_vec_dbl)  ParamDB::put<vec_dbl>;
%template(put_str)      ParamDB::put<std::string>;
%template(put_spdb)     ParamDB::put<ParamDB::SP_db>;
}

// Other components
%shared_ptr(poropy::Assembly)
%shared_ptr(poropy::Core)
%shared_ptr(poropy::BaseDataModel)
%shared_ptr(poropy::SimpleDataModel)
%shared_ptr(poropy::FixedDataModel)
%shared_ptr(poropy::BaseThermalModel)
%shared_ptr(poropy::BaseSolver)
%shared_ptr(poropy::FlareSolver)

%include "Assembly.hh"
%include "Core.hh"
%include "BaseDataModel.hh"
%include "SimpleDataModel.hh"
%include "FixedDataModel.hh"
%include "BaseThermalModel.hh"
%include "BaseSolver.hh"
%include "FlareSolver.hh"

%template(vec_assembly)        std::vector<poropy::Assembly>;
%template(vec_flare_data)      std::vector<poropy::FlareData>;
%template(vec_two_group_data)  std::vector<poropy::TwoGroupData>;

%pythoncode 
%{

def add_assemblies(self, assemblies) :
    for i in range(len(assemblies)) :
        self.add_assembly(assemblies[i])
Core.add_assemblies = add_assemblies

%}

