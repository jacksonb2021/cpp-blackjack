cmake_minimum_required(VERSION 3.26)
project(c_but_better)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(c_but_better
        Test.cpp
        Test.h
        ClackJack_Plus_Plus.cpp)
