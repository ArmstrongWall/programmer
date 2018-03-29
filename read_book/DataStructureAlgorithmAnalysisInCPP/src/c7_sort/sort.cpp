//
// Created by johnny on 3/29/18.
//
#include "sort.h"
template <typename T>
void sort::insertionSort(vector <T> &a) {
    for(int p = 1 ; p < a.size() ; p++ )
    {
        T temp = a[p];
        for (int j = p - 1 ; j > 0 && a[j] < temp; j--) {
            a[j] = std::move(a[j-1]);
        }


    }
}