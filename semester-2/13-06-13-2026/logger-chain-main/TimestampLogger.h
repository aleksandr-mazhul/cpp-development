#pragma once
#include "Logger.h"
#include <string>
class TimestampLogger : public Logger {
public:
    TimestampLogger(Logger* next) : next(next) {}
    void log(LogLevel level, const std::string& message) override {
        std::string stamped = "[t=" + std::to_string(tick++) + "] " + message;
        if (next) next->log(level, stamped);
    }
private:
    Logger* next;
    int tick = 1;
};
