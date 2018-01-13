//
// Created by johnny on 1/11/18.
//
#include <iostream>
#include "BinaryHeap.h"

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
