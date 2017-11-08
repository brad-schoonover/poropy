//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   DBC.hh
 *  @brief  Design-by-Contract macros
 */

#ifndef POROPY_DBC_HH
#define POROPY_DBC_HH

#include <iostream>
#include <string>

#include "poropy_config.h"
#include "GenException.hh"

namespace detran_utilities
{

//===========================================================================//
/**
 *  @page  DBC
 *  @brief Design-By-Contract
 *
 *  DBC is a framework for ensuring consistency between a client's request
 *  and a server's response.  Here, we use a few macro's that help
 *  implement the idea:
 *   - Require: precondition upon entering a method that must be satisfied;
 *              if not satisfied, the client is to blame
 *   - Ensure:  postcondition that must be satisfied for the server to be
 *              correct
 *   - Assert:  a general assertion macro
 *   - Insist:  Conditions that must always be true (i.e. these are always
 *              checked)
 *
 *  See the nice tutorial at:
 *  http://eventhelix.com/realtimemantra/object_oriented/design_by_contract.htm
 *
 */
//===========================================================================//

#ifdef POROPY_ENABLE_DBC

// DBC Macros
#define Assert(c)     if (!(c)) throw poropy::GenException( __LINE__, __FILE__,#c)
#define Require(c)    Assert(c)
#define Ensure(c)     Assert(c)

// DBC Macros with additional message
#define Assert_msg(c, m)     if (!(c)) throw poropy::GenException( __LINE__, __FILE__,std::string(#c)+" "+std::string(m))
#define Require_msg(c, m)    Assert_msg(c, m)
#define Ensure_msg(c, m)     Assert_msg(c, m)

#else

#define Assert(c)   ((void) 0)
#define Require(c)  ((void) 0)
#define Ensure(c)   ((void) 0)
#define Assert_msg(c, m)   ((void) 0)
#define Require_msg(c, m)  ((void) 0)
#define Ensure_msg(c, m)   ((void) 0)

#endif

#define Insist(c,m)   if (!(c)) {std::cerr << m << std::endl; throw poropy::GenException( __LINE__, __FILE__,#c);}

} // end namespace poropy

#endif // POROPY_DBC_HH
