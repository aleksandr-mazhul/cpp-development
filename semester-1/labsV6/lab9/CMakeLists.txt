cmake_minimum_required(VERSION 3.16)

project(lab9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab9
        part1_pract.cpp
        part1.cpp
        part2_pract_tests.cpp
        part2-pract_keybord.cpp
        part2.cpp
)
