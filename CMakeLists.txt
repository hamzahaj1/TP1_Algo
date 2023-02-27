cmake_minimum_required(VERSION 3.5)
project(TP1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Principal.cpp
    Regle.cpp
    Regle.h
    SystemeExpert.cpp
    SystemeExpert.h)

add_executable(TP1 ${SOURCE_FILES})