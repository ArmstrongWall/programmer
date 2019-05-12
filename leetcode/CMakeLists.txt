cmake_minimum_required(VERSION 3.9)
project(leetcode)

find_package(Eigen3 REQUIRED)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

include_directories (
        ${EIGEN3_INCLUDE_DIR}
        ${Sophus_INCLUDE_DIRS}
)

add_executable(leetcode src/main.cpp
        src/206_reverse_linked_list/reverse_linked_list.cpp
        src/92_reverse_linked_list_II/reverse_linked_list_II.cpp src/92_reverse_linked_list_II/reverse_linked_list_II.h)