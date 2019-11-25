cmake_minimum_required(VERSION 3.9)
project(concurrency_in_action)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(Eigen3 REQUIRED)

add_executable(ConcurrencyInAction src/main.cpp
        src/c1_start_thread/c1StartThread.cpp
        src/c2_1_3_wait_threadRAII/RAIIWaitForThread.h
        src/c2_1_3_wait_threadRAII/RAIIWaitForThread.cpp
        src/c4_11_wait_time/wait_time.cpp
        src/c4_11_wait_time/wait_time.h
        src/c5_3_synchronizing_operations/c5_3.cpp
        src/c5_3_synchronizing_operations/c5_3.h
        src/c3_2_unprotected_mutex/unprotected_mutex.cpp
        src/c3_2_unprotected_mutex/unprotected_mutex.h
        src/c3_9_unique_lock/unique_lock.cpp
        src/c3_9_unique_lock/unique_lock.h
        src/c4_1_condition_variable/condition_variable.cpp
        src/c4_1_condition_variable/condition_variable.h
        src/c4_3_threadsafe_queue/threadsafe_queue.cpp
        src/c4_3_threadsafe_queue/threadsafe_queue.h
        src/c6_1_threadsafe_stack/threadsafe_stack.cpp
        src/c6_1_threadsafe_stack/threadsafe_stack.h
        src/c4_1_condition_variable/condition_variable_queue.cpp
        src/c9_1_thread_pool/thread_pool.cpp
        src/c9_1_thread_pool/thread_pool.h)

target_link_libraries(ConcurrencyInAction
        atomic
        )