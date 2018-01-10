cmake_minimum_required(VERSION 3.9)
project(DataStructureAlgorithmAnalysisInCPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(da main.cpp  src/c1/recursion.cpp
                            src/c4_3BinarySearchTree/BinarySearchTree.cpp
                            src/c4_3BinarySearchTree/BinarySearchTree.h
                            src/c4_4AVLTree/AVLTree.cpp
                            src/c4_4AVLTree/AVLTree.h)