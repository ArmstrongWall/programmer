//
// Created by johnny on 3/29/18.
//

#ifndef DATASTRUCTUREALGORITHMANALYSISINCPP_SORT_H
#define DATASTRUCTUREALGORITHMANALYSISINCPP_SORT_H
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

#endif //DATASTRUCTUREALGORITHMANALYSISINCPP_SORT_H
