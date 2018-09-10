cmake_minimum_required(VERSION 3.5)
project(9_eigen)

set(CMAKE_CXX_STANDARD 11)

include_directories("usr/include/eigen3")

add_executable(9_eigen main.cpp)
