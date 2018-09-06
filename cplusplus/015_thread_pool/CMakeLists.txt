cmake_minimum_required(VERSION 3.10)
project(015_thread_pool)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(015_thread_pool main.cpp thread_pool.h)