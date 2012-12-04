#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <iostream>

class Logger {
  Logger();
  /*! We don't need copy constructor.
   */
  Logger(const Logger& rhs);
  /*! We don't need operator=
   */
  Logger& operator=(const Logger& rhs);
 public:
  ~Logger();

  /*! This opertator for simple type such as char*, int ans so on.
    @param[in] logger used logger
    @param[in] var
    @return Reference to logger
   */
  template <typename T>
  friend Logger& operator<<(Logger& logger, const T& var) {
    std::cout << var;
    return logger;
  }

  /*! This one is for ostream stuff such as sdt::endl and so on.
    @param[in] logger used logger
    @param[in] stream pointer to stream copy constructor(?)
    @return Reference to logger
   */
  friend Logger& operator<<(Logger& logger, std::ostream& ( *stream )(std::ostream&))  {
    std::cout << stream;
    return logger;
  }

  /*! GetLogger is friend because we have a private constructor of this class.
    Just another simple Singleton.
    @return Reference to static logger
   */
  friend Logger& GetLogger();
};

/*! Use it for work with logger
 */
Logger& GetLogger();

#endif
