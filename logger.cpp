#include "logger.h"

#include <iostream>

Logger::~Logger() {
}

Logger& GetLogger() {
  static Logger logger;
  return logger;
}

// PRIVATE FUNCS

Logger::Logger() {
}
