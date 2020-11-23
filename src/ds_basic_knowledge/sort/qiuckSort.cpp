//
// Created by wzq on 2020/11/22.
//
#include "sort.h"

template <typename T>
T sort<T>::median3(vector<T> &vec, int left, int right) {
    int center = (left + right) / 2;
    if(vec[left] > vec[center]) {
        swap(vec[center],vec[left]);
    }
    if(vec[center] > vec[right]) {
        swap(vec[center],vec[right]);
    }
    if(vec[left] > vec[center]) {
        swap(vec[left],vec[center]);
    }
    swap(vec[right-1], vec[center]);
    return vec[right-1];
}

template <typename T>
void sort<T>::qiuckSort(vector<T> &vec, int left, int right) {

    if(left >= right) {
        return;
    }
    T pvoit = median3(vec,left,right);

    int i = left;
    int j = right - 1;
    while (true) {
        while (vec[++i] < pvoit) {}
        while (vec[--j] > pvoit) {}
        if(i < j) {
            swap(vec[i],vec[j]);
        } else {
            break;
        }
    }

    swap(vec[i],vec[right-1]);
    qiuckSort(vec,left,i-1);
    qiuckSort(vec,i+1,right);

}

template <typename T>
void sort<T>::qiuckSort_easy(vector<T> &vec, int left, int right) {
    if(left >= right) {
        return;
    }

    T divide = vec[right];

    int i = left;
    int j = right - 1;

    for (;;) {
        while (vec[i] < divide) {i++;}
        while (vec[j] > divide) {j--;}
        if(i < j) {
            std::swap(vec[i],vec[j]);
        } else {
            break;
        }
    }
    std::swap(vec[right],vec[i]);
    qiuckSort_easy(vec,left,i-1);
    qiuckSort_easy(vec,i+1,right);
}
