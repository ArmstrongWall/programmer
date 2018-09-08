#include <iostream>
#include "thread_pool.h"
using namespace thread_pool;

void workFunc1(void* data_) {
    double data = *((double*)data_);
    printf("data = %lf\n", data);
}

int main() {

    double data1[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    ThreadPool<double> threads(12);
    for(int i = 0; i < 12; ++i)
        threads.reduce(i, workFunc1, data1[i]);
    return 0;
}


