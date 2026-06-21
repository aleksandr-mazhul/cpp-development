cmake_minimum_required(VERSION 3.16)

project(cpp_semester_2_13_06_13_2026_logger_chain_main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_semester_2_13_06_13_2026_logger_chain_main
    "ConsoleLogger.cpp"
    "FileLogger.cpp"
    "FilteringLogger.cpp"
    "Logger.cpp"
    "LogLevel.cpp"
    "workshop_logger_chain.cpp"
)
