cmake_minimum_required(VERSION 3.16)

project(semester_2_exam_first_iteration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(semester_2_exam_first_iteration
    "Employee.cpp"
    "EmployeesIO.cpp"
    "main.cpp"
)
