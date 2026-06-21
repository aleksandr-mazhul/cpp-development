#pragma once
#include "Logger.h"
#include <iostream>
class FilteringLogger : public Logger {
public:
    FilteringLogger(LogLevel threshold, Logger* next) : threshold(threshold), next(next) {}
    void log(LogLevel level, const std::string& message) override {
        if (level >= threshold) { if (next) next->log(level, message); }
        else { std::cout << " [filter] отброшено: " << level << " (" << message << ")" << std::endl; }
    }
private:
    LogLevel threshold;
    Logger* next;
};
