cmake_minimum_required(VERSION 3.9)
project(cpp_exercise)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(cpp_exercise main.cpp
        src/001_bind/bind.cpp
        src/002_thread_pool/thread_pool.cpp src/002_thread_pool/thread_pool.h)