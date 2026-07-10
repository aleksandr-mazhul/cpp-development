cmake_minimum_required(VERSION 3.16)

project(kontrolnaya LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(kontrolnaya
        kr1.cpp
        kr2.cpp
        kr3.cpp
        kr3Armstrong.cpp
)
