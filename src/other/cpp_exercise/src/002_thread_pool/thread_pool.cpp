//
// Created by wzq on 18-10-7.
//

//#include <iostream>
//#include "thread_pool.h"
//

//using namespace thread_pool;
//
//void workFunc1(void* data_) {
//    double data = *((double*)data_);
//    printf("data = %lf\n", data);
//}
//
//int thread_pool_demo() {
//
//    double data1[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
//    ThreadPool<double> threads(13);//13 pool
//    for(int i = 0; i < 13; ++i)
//        threads.reduce(i, workFunc1, data1[i]);
//    return 0;
//}

#include <iostream>
#include <vector>
#include <chrono>

#include "thread_pool2.h"

int thread_pool_demo()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
                pool.enqueue([i] {
                    std::cout << "hello " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "world " << i << std::endl;
                    return i*i;
                })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}