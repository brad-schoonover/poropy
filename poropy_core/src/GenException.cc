//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   GenException.cc
 *  @brief  Member definitions of class GenException
 */
//---------------------------------------------------------------------------//

#include <sstream>

#include "GenException.hh"

namespace poropy
{

std::string GenException::prepend = "poropy exception";

//---------------------------------------------------------------------------//
GenException::GenException()
{
  myMessage = prepend;
}

//---------------------------------------------------------------------------//
GenException::GenException(int line, std::string file, std::string msg)
{
  std::stringstream sline;
  sline << line;
  myMessage = prepend + "\n"
    + "           on line: " + sline.str() + "\n"
    + "           in file: " + file + "\n"
    + "           message: " + msg;
}

//---------------------------------------------------------------------------//
const char* GenException::what() const throw()
{
	return myMessage.c_str();
}

//---------------------------------------------------------------------------//
GenException::~GenException() throw() 
{
  /* ... */
}

} // end namespace poropy
