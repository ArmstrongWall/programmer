//
// Created by wzq on 2020/11/22.
//
#include "sort.h"

template <typename T>
void sort<T>::bubbleSort(vector<T> &vec) {

    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec.size() - i; j++) {
            if(vec[j] > vec[j+1]) {
                std::swap(vec[j],vec[j+1]);
            }
        }
    }
}