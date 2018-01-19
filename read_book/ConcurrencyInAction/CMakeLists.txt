cmake_minimum_required(VERSION 3.9)
project(ConcurrencyInAction)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(ConcurrencyInAction main.cpp)