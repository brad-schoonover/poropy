//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   GenException.hh
 *  @brief  GenException class definition.
 */
//---------------------------------------------------------------------------//

#ifndef POROPY_GENEXCEPTION_HH
#define POROPY_GENEXCEPTION_HH

#include <iostream>
#include <exception>
#include <string>

namespace poropy
{

/**
 *  A generic mechanism to manually manage exceptions
 */
class GenException: public std::exception
{

public:

  /// Constructs a new GenException with the default message.
  GenException();

  /**
   * @brief Constructs a new GenException with a provided message
   *
   * @param line line of code erring
   * @param file file in which error occurs
   * @param msg the message
   */
  GenException(int line, std::string file, std::string msg);

  /**
   * Returns the error message associated with this GenException.
   *
   * @return the message
   */
  virtual const char* what() const throw ();

  /**
   * Destroys this GenException.
   */
  virtual ~GenException() throw ();


protected:

  /// The message associated with this exception.
  std::string myMessage;
  /// A string to prepend to all message of this class.
  static std::string prepend;

};

/// Easy macro for throwing exceptions.
#define THROW(m) throw poropy::GenException(__LINE__,__FILE__,m);

} // end namespace poropy

#endif // POROPY_GENEXCEPTION_HH
