//
// Created by Johnny on 2020/11/8.
//

#include "sort.h"
#include "bubbleSort.cpp"
#include "insertionSort.cpp"
#include "mergeSort.cpp"
#include "qiuckSort.cpp"
#include "selectSort.cpp"
#include "shellSort.cpp"

template <typename T>
sort<T>::sort() {

}

template <typename T>
sort<T>::~sort() {

}

template <typename T>
void sort<T>::print(vector<T> &a) {
    for(auto x: a) {
        cout << x << ", ";
    }
    std::cout << std::endl;
}


void sortDemo() {
    std::cout << "Sort Demo" << std::endl;

    auto sorter = new sort<int>;
    vector<int> a {8, 1, 4, 9, 6, 3, 5, 2, 7, 0};

//    sorter->insertionSort(a);
//    sorter->insertionSort1(a);

//    sorter->bubbleSort(a);
//    sorter->selectSort(a);

//    sorter->mergeSort(a);
//    sorter->mergeSort1(a);

//    sorter->qiuckSort(a,0,a.size()-1);
    sorter->qiuckSort_easy(a,0,a.size()-1);
    sorter->print(a);


}