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
        src/92_reverse_linked_list_II/reverse_linked_list_II.cpp
        src/92_reverse_linked_list_II/reverse_linked_list_II.h
        src/160_get_intersection_node/getIntersectionNode.cpp
        src/160_get_intersection_node/getIntersectionNode.h
        src/142_detectCycle/detectCycle.cpp
        src/142_detectCycle/detectCycle.h
        src/86_partition_list/partition_list.cpp
        src/86_partition_list/partition_list.h
        src/138_copyRandomList/copyRandomList.cpp
        src/138_copyRandomList/copyRandomList.h
        src/21_mergeTwoLists/mergeTwoLists.cpp
        src/21_mergeTwoLists/mergeTwoLists.h
        src/23_mergeKLists/mergeKLists.cpp
        src/23_mergeKLists/mergeKLists.h
        src/224_basicCalculator/basic_calculator.cpp
        src/224_basicCalculator/basic_calculator.h)