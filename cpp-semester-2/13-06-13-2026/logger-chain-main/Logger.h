#pragma once
#include "LogLevel.h"

#include <string>

class Logger
{
  public:
    virtual ~Logger() = default;
    virtual void log(LogLevel level, const std::string& message) = 0;
};
