#include <iostream>
#include "thread_pool.h"
using namespace thread_pool;

void workFunc1(void* data_) {
    double data = *((double*)data_);
    printf("data = %lf\n", data);
}

int main() {

    double data1[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    ThreadPool<double> threads(13);//13 pool
    for(int i = 0; i < 13; ++i)
        threads.reduce(i, workFunc1, data1[i]);
    return 0;
}


