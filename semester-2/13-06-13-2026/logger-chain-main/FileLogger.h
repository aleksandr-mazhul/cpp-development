#pragma once
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>

class FileLogger : public Logger
{
public:
    FileLogger(const std::string& filename = "log.txt") : filename(filename) {
        std::ofstream file(filename, std::ios::trunc);
    }

    void log(LogLevel level, const std::string& message) override
    {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << level << ": " << message << "\n";
        }
    }

    void dump() const
    {
        std::cout << "=== Содержимое файла " << filename << " ===\n";
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }

private:
    std::string filename;
};
