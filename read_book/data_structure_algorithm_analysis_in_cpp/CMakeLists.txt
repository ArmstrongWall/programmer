cmake_minimum_required(VERSION 3.9)
project(DataStructureAlgorithmAnalysisInCPP)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(da main.cpp
        src/c1/recursion.cpp
        src/c4_3BinarySearchTree/BinarySearchTree.cpp       src/c4_3BinarySearchTree/BinarySearchTree.h
        src/c4_4AVLTree/AVLTree.cpp                         src/c4_4AVLTree/AVLTree.h
        src/c6_3BinaryHeap/BinaryHeap.cpp                   src/c6_3BinaryHeap/BinaryHeap.h
        include.h
        src/c7_sort/sort.cpp                                src/c7_sort/sort.h)