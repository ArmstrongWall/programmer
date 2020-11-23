//
// Created by wzq on 2020/11/22.
//
#include "sort.h"
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
