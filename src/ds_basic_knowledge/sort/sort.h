//
// Created by Johnny on 2020/11/8.
//

#ifndef LEETCODE_SORT_H
#define LEETCODE_SORT_H


#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class sort{
public:
    sort();
    ~sort();
    //! classic sort method
    void insertionSort(vector<T> &a);
    void insertionSort1(vector<T> &a);

    void mergeSort(vector<T> &vec);
    void mergeSort1(vector<T> &vec);

    void shellSort(vector<T> &a);
    void bubbleSort(vector<T> &vec);


    void selectSort(vector<T> &vec);
    T median3(vector<T> &vec, int left, int right);
    void qiuckSort(vector<T> &vec, int left, int right);
    void qiuckSort_easy(vector<T> &vec, int left, int right);

    //! auxiliary tool
    void mergesort_two_vec(std::vector<T>& sub_vec_1,
                           std::vector<T>& sub_vec_2,
                           std::vector<T>& vec_);
    void mergesort_two_vec1(std::vector<T>& sub_vec_1,
                            std::vector<T>& sub_vec_2,
                            std::vector<T>& vec_);

    void print(vector<T> &a);
};

void sortDemo();

#endif //LEETCODE_SORT_H
