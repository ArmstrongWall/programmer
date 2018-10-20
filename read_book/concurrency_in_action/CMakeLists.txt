cmake_minimum_required(VERSION 3.9)
project(ConcurrencyInAction)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(ConcurrencyInAction src/main.cpp
        src/c1_start_thread/c1StartThread.cpp
        src/c2_1_3_wait_threadRAII/RAIIWaitForThread.h
        src/c2_1_3_wait_threadRAII/RAIIWaitForThread.cpp
        src/c4_3_wait_time/wait_time.cpp
        src/c4_3_wait_time/wait_time.h src/c5_3_synchronizing_operations/c5_3.cpp src/c5_3_synchronizing_operations/c5_3.h src/c3_2_unprotected_mutex/unprotected_mutex.cpp src/c3_2_unprotected_mutex/unprotected_mutex.h src/c3_9_unique_lock/unique_lock.cpp src/c3_9_unique_lock/unique_lock.h)