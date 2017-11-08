//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   ParamDB.hh
 *  @brief  ParamDB class definition.
 */
//---------------------------------------------------------------------------//

#ifndef poropy_PARAMDB_HH_
#define poropy_PARAMDB_HH_

#include "Definitions.hh"

#include <memory>
#include <string>
#include <map>


namespace poropy
{

//---------------------------------------------------------------------------//
/**
 *  @class ParamDB
 *  @brief Flexible storage for user input.
 *
 *  Having a dynamic parameter database allows new parameters to be
 *  added without having any fixed parser be updated.
 */
//---------------------------------------------------------------------------//

class ParamDB
{

public:

  //-------------------------------------------------------------------------//
  // TYPEDEFS
  //-------------------------------------------------------------------------//

  enum INPUT_TYPES
  {
    INT,
    DBL,
    STR,
    VEC_INT,
    VEC_DBL,
    SPINPUT
  };

  typedef std::shared_ptr<ParamDB> SP_db;

  //-------------------------------------------------------------------------//
  // CONSTRUCTOR & DESTRUCTOR
  //-------------------------------------------------------------------------//

  /// Constructor with optional name
  ParamDB(std::string name = "ParamDB");

  //-------------------------------------------------------------------------//
  // PUBLIC FUNCTIONS
  //-------------------------------------------------------------------------//

  /**
   *  @brief Return value of key
   *  @param    key     Name of the parameter.
   *  @param    value   Reference to which parameter value is assigned.
   *  @return           Check whether key is found.
   */
  template <class T>
  inline T get(const std::string &key) const
  {

  }

  /**
   *  @brief Check if the key is in a  map.
   *
   *  Note, if used consistently, this will prevent the
   *  same key being used for different value types.
   *  Maybe there's a better way to do this input
   *  structure.
   *
   *  @param    key     Name of the parameter.
   *  @return           True if exists; false otherwise.
   */
  inline bool check(const std::string &key) const;

  /**
   *  @brief Put a key and value in the database.
   *  @param    key         Name of the parameter.
   *  @param    value       Reference to which parameter value is assigned.
   *  @param    replace     Can we replace a current value?
   *  @return               Check whether key is found.
   */
  template <class T>
  inline void put(const std::string &key, const T value)
  {

  }

  /// Return a map
  template <class T>
  const std::map<std::string, T>& get_map();

  /// Number of entries of a certain type.
  int size(int type) const;

  /// Display all my contents.
  void display() const;

private:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  /// Name of the database
  std::string d_name;
  /// Integer parameters.
  std::map<std::string, int> d_data_int;
  /// Double parameters.
  std::map<std::string, double> d_data_dbl;
  /// Integer vector parameters.
  std::map<std::string, vec_int> d_data_vec_int;
  /// Double vector parameters.
  std::map<std::string, vec_dbl> d_data_vec_dbl;
  /// String parameters.
  std::map<std::string, std::string> d_data_str;
  /// ParamDB parameters
  std::map<std::string, SP_db> d_data_db;

  //-------------------------------------------------------------------------//
  // IMPLEMENTATION
  //-------------------------------------------------------------------------//

};

} // end namespace poropy

//---------------------------------------------------------------------------//
// INLINE FUNCTIONS
//---------------------------------------------------------------------------//

#include "ParamDB.i.hh"

#endif /* poropy_PARAMDB_HH_ */
