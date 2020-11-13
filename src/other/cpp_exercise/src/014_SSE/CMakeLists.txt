cmake_minimum_required(VERSION 3.12)
project(014_SSE)
add_definitions("-DENABLE_SSE")
set(CMAKE_CXX_FLAGS "${SSE_FLAGS} -O3 -fPIC -g -march=native")
set(CMAKE_CXX_STANDARD 14)

add_executable(014_SSE main.cpp)