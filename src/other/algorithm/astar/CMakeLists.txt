cmake_minimum_required(VERSION 3.9)
project(astar)

set(CMAKE_CXX_STANDARD 11)

add_executable(astar
        src/astar/astar.cpp
        src/astar/astar.h
        src/main.cpp)
