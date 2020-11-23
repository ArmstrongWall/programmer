//
// Created by wzq on 2020/11/22.
//
#include "sort.h"

template <typename T>
void sort<T>::mergeSort(vector <T> &vec) {

    if (vec.size() <= 1) {
        return;
    }

    std::vector<T> sub_vec_1;
    std::vector<T> sub_vec_2;

    int mid = vec.size() / 2;

    for (int i = 0; i < mid; i++) {
        sub_vec_1.push_back(vec[i]);
    }

    for (int i = mid; i < vec.size(); i++) {
        sub_vec_2.push_back(vec[i]);
    }

    mergeSort(sub_vec_1);
    mergeSort(sub_vec_2);

    mergesort_two_vec(sub_vec_1, sub_vec_2, vec);
}

template <typename T>
void sort<T>::mergesort_two_vec(std::vector<T>& sub_vec_1,
                                std::vector<T>& sub_vec_2,
                                std::vector<T>& vec_) {
    int i = 0;
    int j = 0;

    vec_.clear();

    while (i < sub_vec_1.size() && j < sub_vec_2.size()) {
        if(sub_vec_1[i] <= sub_vec_2[j]) {
            vec_.push_back(sub_vec_1[i]);
            i++;
        } else {
            vec_.push_back(sub_vec_2[j]);
            j++;
        }
    }
    for(;i < sub_vec_1.size(); i++) {
        vec_.push_back(sub_vec_1[i]);
    }
    for(;j < sub_vec_2.size(); j++) {
        vec_.push_back(sub_vec_2[j]);
    }
}


template <typename T>
void sort<T>::mergeSort1(vector <T> &vec) {
    if (vec.size() <= 1) {
        return;
    }

    std::vector<T> sub_vec_1;
    std::vector<T> sub_vec_2;

    int mid = vec.size() / 2;

    for (int i = 0; i < mid; i++) {
        sub_vec_1.push_back(vec[i]);
    }

    for (int i = mid; i < vec.size(); i++) {
        sub_vec_2.push_back(vec[i]);
    }

    mergeSort1(sub_vec_1);
    mergeSort1(sub_vec_2);
    mergesort_two_vec1(sub_vec_1,sub_vec_2,vec);

}
template <typename T>
void sort<T>::mergesort_two_vec1(std::vector<T>& sub_vec_1,
                                 std::vector<T>& sub_vec_2,
                                 std::vector<T>& vec_) {
    vec_.clear();
    int sub1_index = 0;
    int sub2_index = 0;

    while(true) {
        if(sub_vec_1[sub1_index] < sub_vec_2[sub2_index]) {
            vec_.push_back(sub_vec_1[sub1_index]);
            sub1_index++;
        } else {
            vec_.push_back(sub_vec_2[sub2_index]);
            sub2_index++;
        }
        if(sub1_index == sub_vec_1.size() || sub2_index == sub_vec_2.size()) {
            break;
        }
    }

    for(int i = sub1_index; i < sub_vec_1.size(); i++) {
        vec_.push_back(sub_vec_1[i]);
    }

    for(int i = sub2_index; i < sub_vec_2.size(); i++) {
        vec_.push_back(sub_vec_2[i]);
    }




}

