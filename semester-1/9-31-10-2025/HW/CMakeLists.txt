cmake_minimum_required(VERSION 3.16)

project(hw_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hw_2
        my_try.cpp
        taylor_sin.cpp
)
