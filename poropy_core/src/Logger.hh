#ifndef POROPY_LOGGER_HPP
#define POROPY_LOGGER_HPP

#include "Definitions.hh"

#include <fstream>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

namespace poropy
{

class Logger
{

public:

  enum LOG_TYPE
  {
    LOG_ERROR, LOG_WARNING, LOG_INFO, END_LOG_TYPE
  };

  enum LOG_LEVEL
  {
    NONE, VERBOSE, DEBUG, END_LOG_LEVEL
  };

  explicit Logger (const char *fname = "poropy_log.txt",
                   size_t log_level)
    : number_warnings (0U)
    , number_errors (0U)
  {
    my_file.open(fname);
    if (my_file.is_open())
    {
      my_file << "Log file created" << std::endl << std::endl;
    }
  }

  ~Logger ()
  {
    if (my_file.is_open ())
    {
      my_file << std::endl << std::endl;
      // Report number of errors and warnings
      my_file << number_warnings << " warnings" << std::endl;
      my_file << number_errors << " errors" << std::endl;
      my_file.close ();
    }
  }

  // Overload << operator using log type
  friend Logger &
  operator << (Logger &logger, const size_t l_type)
  {
    switch (l_type)
    {
      case poropy::Logger::LOG_ERROR :
        logger.my_file << "[ERROR]: ";
        ++logger.number_errors;
        break;
      case poropy::Logger::LOG_WARNING:
        logger.my_file << "[WARNING]: ";
        ++logger.number_warnings;
        break;
      default:
        logger.my_file << "[INFO]: ";
        break;
    }
    return logger;
  }

  // Overload << operator using C style strings
  // No need for std::string objects here
  friend Logger &
  operator << (Logger &logger, const char *text)
  {
    logger.my_file << text << std::endl;
    return logger;
  }

  // Make it Non Copyable (or you can inherit from sf::NonCopyable if you want)
  Logger (const Logger &) = delete;
  Logger& operator= (const Logger &) = delete;

  void formatted_log(char const* format, ...)
  {
    char buffer[250];
    va_list args;
    va_start(args, format);
    int n = vsprintf(buffer, format, args);
    va_end(args);
    std::string s(buffer, n);
    my_file << s << std::endl;
  }

private:

  std::ofstream my_file;
  size_t number_warnings;
  size_t number_errors;

};

} // namespace poropy

#endif // POROPY_LOGGER_HPP
