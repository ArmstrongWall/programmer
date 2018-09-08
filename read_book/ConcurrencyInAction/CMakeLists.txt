cmake_minimum_required(VERSION 3.9)
project(ConcurrencyInAction)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(ConcurrencyInAction main.cpp
        src/c1StartThread/c1StartThread.cpp
        src/c2_1_3RAIIWaitForThread/RAIIWaitForThread.h
        src/c2_1_3RAIIWaitForThread/RAIIWaitForThread.cpp
        src/c4_3wait_time/wait_time.cpp
        src/c4_3wait_time/wait_time.h src/c5_3_synchronizing_operations/c5_3.cpp src/c5_3_synchronizing_operations/c5_3.h)