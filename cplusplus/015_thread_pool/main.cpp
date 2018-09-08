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


//#include <atomic>
//#include <thread>
//#include <assert.h>
//
//std::atomic_bool x,y;
//std::atomic_int z;
//void write_x()
//{
//    x.store(true,std::memory_order_seq_cst);
//}
//void write_y()
//{
//    y.store(true,std::memory_order_seq_cst);
//}
//void read_x_then_y()
//{
//    while(!x.load(std::memory_order_seq_cst));
//    if(y.load(std::memory_order_seq_cst))++z;
//}
//void read_y_then_x()
//{
//    while(!y.load(std::memory_order_seq_cst));
//    if(x.load(std::memory_order_seq_cst))++z;
//}
//int main()
//{
//    x=false;
//    y=false;
//    z=0;
//    std::thread a(write_x);
//    std::thread b(write_y);
//    std::thread c(read_x_then_y);
//    std::thread d(read_y_then_x);
//    a.join();
//    b.join();
//    c.join();
//    d.join();
//    assert(z.load()!=2);
//    //if !(z.load()!=0) abort => if z.load()==0 abort
//}