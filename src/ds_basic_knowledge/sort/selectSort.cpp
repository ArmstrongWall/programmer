//
// Created by wzq on 2020/11/22.
//
#include "sort.h"
//找到遍历i个元素中最小的与之替换
template <typename T>
void sort<T>::selectSort(vector<T> &vec) {
    for(int i = 0; i < vec.size(); i++) {
        int min_index = i;
        for(int j = i; j < vec.size(); j++) {
            if(vec[j] < vec[min_index]) {
                min_index = j;
            }
        }
        std::swap(vec[i],vec[min_index]);
    }
}