cmake_minimum_required(VERSION 3.15)
project(rational)

set(CMAKE_CXX_STANDARD 14)

add_executable(rational main.cpp biginteger.h rational.h)