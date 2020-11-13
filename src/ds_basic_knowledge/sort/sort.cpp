//
// Created by Johnny on 2020/11/8.
//

#include "sort.h"


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

template <typename T>
void sort<T>::insertionSort(vector <T> &a) {
    for(int p = 1 ; p < a.size() ; p++ ) {
        T temp = std::move(a[p]);
        int j = 0;
        for (j = p ; j > 0 && a[j-1] > temp; j--) {
            //once find small value , break out to insert
            a[j] = std::move(a[j-1]);
        }
        a[j] = std::move(temp);
    }
}

template <typename T>
void sort<T>::insertionSort1(vector <T> &a) {
    for(int i = 1; i < a.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(a[j] < a[j-1]) {
                std::swap(a[j-1],a[j]);
            }
        }
    }

}


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
template <typename T>
void sort<T>::shellSort(vector<T> &a) {
    //ensure gap,define how to grouping

    //use insertionSort to different group
}

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