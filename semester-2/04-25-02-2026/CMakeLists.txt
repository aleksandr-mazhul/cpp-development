cmake_minimum_required(VERSION 3.16)

project(semester_2_04_25_02_2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(semester_2_04_25_02_2026
    "bank.cpp"
    "bankAccount/BankAccount.cpp"
    "bankAccount/Bankservice.cpp"
    "bankAccount/main.cpp"
    "counter/counter.cpp"
    "counter/main.cpp"
    "queue/main.cpp"
    "timer/main.cpp"
    "timer/Timer.cpp"
)
