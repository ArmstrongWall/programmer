//
// Created by johnny on 3/29/18.
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
        cout << x << endl;
    }
}

template <typename T>
void sort<T>::insertionSort(vector <T> &a) {
    for(int p = 1 ; p < a.size() ; p++ )
    {
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
void sort<T>::shellSort(vector<T> &a) {
    //ensure gap,define how to grouping

    //use insertionSort to different group
}


