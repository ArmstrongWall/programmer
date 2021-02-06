/**
* This file is part of programmer.
* Description: 
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* programmer is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* programmer is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with programmer. If not, see <http://www.gnu.org/licenses/>.
*
* @file        binary_heap.cpp.c
* @brief       Defines the 
* @author      Ziqiang Wang
* @email       1531651@tongji.edu.cn
* @date        2021/1/8
* @copyright   Copyright (c) 2021
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2021/1/8    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*/

#include "binary_heap.h"



template <typename T>
BinaryHeap<T>::BinaryHeap(unsigned long capacity) {
    array.resize(capacity);
    array = {0,13,21,16,24,31,19,68,65,26,32};
    currentSize = 10;
}

template <typename T>
void BinaryHeap<T>::insert(const T & x) {
    //expand capacity
    if( currentSize == array.size() - 1 ) {
        array.resize(array.size()*2);
    }

    currentSize+=1;
    auto hole_index = currentSize;
    auto insert_node = std::move(x);
    //percolateUp
    while (insert_node < array[hole_index / 2]) {
        array[hole_index] = array[hole_index/2];//swap father and child
        hole_index /= 2;
    }
    //fill insert_node
    array[hole_index] = std::move(insert_node);
}

template <typename T>
void BinaryHeap<T>::deletMin(T &item) {

}

template <typename T>
void BinaryHeap<T>::printBinaryHeap() {
    printBinaryHeap(array[1],1);
}

template <typename T>
void BinaryHeap<T>::printBinaryHeap(const T &node,const unsigned long & index) {

    if(index <= currentSize)
    {
        printBinaryHeap(array[2*index],2*index);
        cout << node << endl;
        printBinaryHeap(array[2*index+1],2*index+1);
    }
//    for(auto x : array) {
//        cout << x << endl;
//    }
}

void BinaryHeapDemo() {
    std::cout << "Binary Heap Demo" << std::endl;
    auto heap = new BinaryHeap<int>;
    std::cout << "before insert" << std::endl;
    heap->printBinaryHeap();

    heap->insert(14);
    std::cout << "after insert" << std::endl;
    heap->printBinaryHeap();
}