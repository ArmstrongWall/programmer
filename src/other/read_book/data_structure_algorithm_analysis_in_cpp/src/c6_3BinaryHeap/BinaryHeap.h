//
// Created by johnny on 1/11/18.
//

#ifndef DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYHEAP_H
#define DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYHEAP_H

#include <vector>

using namespace std;

template <typename T>
class BinaryHeap{

public:
    explicit BinaryHeap(unsigned long capacity = 1 );
    explicit BinaryHeap( const vector<T> & items );
    void isEmpty() const ;

    void insert(const T & x);
    void deletMin();
    void deletMin(T & item);
    void makeEmpty();
    void printBinaryHeap();
    void printBinaryHeap(const T &node,const unsigned long & index);

private:
    unsigned long currentSize;
    vector<T> array;
    void buildHeap();
    void percolateDown(int hole);

};

void BinaryHeapDemo();

#endif //DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYHEAP_H
