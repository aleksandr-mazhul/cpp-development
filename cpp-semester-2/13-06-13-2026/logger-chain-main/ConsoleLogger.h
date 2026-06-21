#pragma once
#include "Logger.h"
#include <iostream>
class ConsoleLogger : public Logger {
public:
    void log(LogLevel level, const std::string& message) override {
        std::cout << " [console] " << level << ": " << message << std::endl;
    }
};
