//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   BaseDataModel.cc
 *  @brief  BaseDataModel class member definitions.
 */
//---------------------------------------------------------------------------//

#include "BaseDataModel.hh"

namespace poropy
{

//---------------------------------------------------------------------------//
BaseDataModel::BaseDataModel(ParamDB::SP_db db)
  : _db(db)
{
  /* ... */
}

//---------------------------------------------------------------------------//
BaseDataModel::~BaseDataModel()
{
  /* ... */
}

} // namespace poropy
