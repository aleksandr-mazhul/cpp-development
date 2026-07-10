cmake_minimum_required(VERSION 3.16)

project(cpp_semester_2_06_18_03_2026_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_semester_2_06_18_03_2026_task
        filters.cpp
        main.cpp
        predicates.cpp
)
