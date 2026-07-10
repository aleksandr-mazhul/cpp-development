#pragma once
#include <iostream>
enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error
};

inline std::ostream& operator<<(std::ostream& os, LogLevel level)
{
    switch (level)
    {
        case LogLevel::Debug:
            os << "Debug";
            break;
        case LogLevel::Info:
            os << "Info";
            break;
        case LogLevel::Warning:
            os << "Warning";
            break;
        case LogLevel::Error:
            os << "Error";
            break;
    }
    return os;
}
