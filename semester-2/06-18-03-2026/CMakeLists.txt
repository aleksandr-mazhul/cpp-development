cmake_minimum_required(VERSION 3.16)

project(semester_2_06_18_03_2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(semester_2_06_18_03_2026
    "main.cpp"
    "task/filters.cpp"
    "task/main.cpp"
    "task/predicates.cpp"
)
