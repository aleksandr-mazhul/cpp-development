cmake_minimum_required(VERSION 3.16)

project(semester_2_debug_lab_src LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(semester_2_debug_lab_src
    "main.cpp"
    "math_utils.cpp"
)
