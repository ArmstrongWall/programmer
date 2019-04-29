cmake_minimum_required(VERSION 3.9)
project(cpp_exercise)

find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

include_directories (
        ${EIGEN3_INCLUDE_DIR}
        ${Sophus_INCLUDE_DIRS}
)

add_executable(cpp_exercise src/main.cpp
        src/001_bind/bind.cpp
        src/002_thread_pool/thread_pool.cpp src/002_thread_pool/thread_pool.h
        src/003_chrono_time/chrono_time.cpp src/003_chrono_time/chrono_time.h
        src/004_lambda/lambda.cpp src/004_lambda/lambda.h
        src/005_eigen/eigen.cpp src/005_eigen/eigen.h
        src/006_std_move/std_move.cpp src/006_std_move/std_move.h
        src/007_random/random.h
        src/008_insert_sort/insert_sort.cpp src/008_insert_sort/insert_sort.h
        src/011_basic_datastructure/vector/vector.cpp src/011_basic_datastructure/vector/vector.h)