cmake_minimum_required(VERSION 3.9)
project(cpp_exercise)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

add_executable(cpp_exercise main.cpp
        src/001_bind/bind.cpp
        src/002_thread_pool/thread_pool.cpp src/002_thread_pool/thread_pool.h
        src/003_chrono_time/chrono_time.cpp src/003_chrono_time/chrono_time.h
        src/004_lambda/lambda.cpp src/004_lambda/lambda.h
        src/005_eigen/eigen.cpp src/005_eigen/eigen.h)