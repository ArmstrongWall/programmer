/**
 * Copyright© 2016-2018. UISEE (SHANGHAI) AUTOMOTIVE TECHNOLOGIES LTD. All rights reserved.
 * LICENSE AGREEMENT
 * The copy of the SOFTWARE is licensed, not sold.
 * Customer owns any media on which the SOFTWARE is recorded, but UISEE and its licensors or
 * suppliers retain ownership of the copy of the SOFTWARE itself, including all copyrights and
 * other intellectual property rights in and to the SOFTWARE (including but not limited to all
 * images, photographs, animations, video, audio, music, text, and other information incorporated
 * into the SOFTWARE), the accompanying printed materials, and any copies of the SOFTWARE.
 * The SOFTWARE is protected by copyright laws and international treaty provisions. Accordingly,
 * Customer is required to treat the SOFTWARE like any other copyrighted material,except as
 * otherwise allowed pursuant to this AGREEMENT and that it may make one copy of the SOFTWARE
 * solely for backup or archive purposes, provided that Customer reproduces all copyright and
 * proprietary notices that are on the original copy. The algorithms, structure, organization
 * and source code of the SOFTWARE are the valuable trade secrets and confidential
 * information of UISEE. Except as otherwise expressly provided herein, neither this AGREEMENT
 * nor UISEE grants Customer any express or implied right under any UISEE patents, copyrights,
 * trademarks, or other intellectual property rights in the SOFTWARE, and all rights, title
 * and interest in and to the SOFTWARE not expressly granted are reserved by UISEE or its
 * licensors or suppliers.
 *
 * @file   thread_pool.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-11-21
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-11-21    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#include <iostream>
#include <unistd.h>
#include <functional>
#include <numeric>
#include <eigen3/Eigen/Dense>

#include"thread_pool.h"
typedef Eigen::Matrix<double,6,6> Mat66;


double get_machine_timestamp_s() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tp = std::chrono::time_point_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    return (static_cast<double>(timestamp)) / 1000000.0;
}

void printnum() {
    std::cout<<"10"<<std::endl;
}

template<typename Iterator,typename T>
struct accumulate_block {
    T operator()(Iterator first,Iterator last) { // 1
        return std::accumulate(first,last,T());  // 2
    }
};

template<typename Iterator>
Mat66 sum_value_mat(Iterator first, Iterator last) {
    Mat66 value = Mat66::Zero();
    for(auto it = first; it < last; it++) {
        value += *it;
    }
    return value;
}

template<typename Iterator,typename T>
T sum_value(Iterator first, Iterator last) {
    T value;
    for(auto it = first; it < last; it++) {
        value += *it;
    }
    return value;
}


template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init) {
    unsigned long const length=std::distance(first,last);
    if(!length)
        return init;
    unsigned long const block_size = 50000;
    unsigned long const num_blocks=(length+block_size-1)/block_size;
    std::vector<std::future<T> > futures(num_blocks-1);
    thread_pool pool;
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
//        futures[i] = pool.submit([block_start, block_end]() {
//                                     accumulate_block<Iterator, T> a;
//                                     return a(block_start, block_end);});

        futures[i] = pool.submit([block_start, block_end]() {
            return sum_value<Iterator, T>(block_start, block_end);
        });

        block_start = block_end;
    }
    T last_result   = accumulate_block<Iterator,T>()(block_start,last);
    T result        = init;
    for(unsigned long i = 0; i<(num_blocks-1);++i) {
        result      += futures[i].get();
    }
    result          += last_result;
    return result;
}

template<typename Iterator,typename T>
T parallel_accumulate_mat(Iterator first,Iterator last,T init, unsigned long const block_size) {
    unsigned long const length=std::distance(first,last);
    if(!length)
        return init;
//    unsigned long const block_size = 25000;
    unsigned long const num_blocks=(length+block_size-1)/block_size;
    std::vector<std::future<T> > futures(num_blocks-1);
    thread_pool pool;
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
//        futures[i] = pool.submit([block_start, block_end]() {
//                                     accumulate_block<Iterator, T> a;
//                                     return a(block_start, block_end);});

        futures[i] = pool.submit([block_start, block_end]() {
            return sum_value_mat<Iterator>(block_start, block_end);
        });

        block_start = block_end;
    }
    T last_result   = sum_value_mat<Iterator>(block_start,last);
    T result        = init;
    for(unsigned long i = 0; i<(num_blocks-1);++i) {
        result      += futures[i].get();
    }
    result          += last_result;
    return result;
}

int thread_pool_demo() {

    std::vector<long> values(1000000,10); // empty vector
//    for(long i = 0; i < values.size(); i++) {
//        values[i] = i;
//    }

    long count = 1000;

    double t1,t2,sum_time = 0;

    for(int i = 0; i < count; i++) {

        t1 = get_machine_timestamp_s();
        long parallelResult = parallel_accumulate(values.begin(), values.end(), 0);
        t2 = get_machine_timestamp_s();
        sum_time += t2 - t1;
        std::cout << "para time : " << sum_time/(i+1)  << ",res :" << parallelResult <<"\n";
    }

    sleep(1);
    std::cout << "no para ........................." <<"\n";

    sum_time = 0;
    for(int i = 0; i < count; i++) {
        int sum = 0;
        t1 = get_machine_timestamp_s();
        for(auto x : values) {
            sum += x;
        }
        t2 = get_machine_timestamp_s();
        sum_time += t2 - t1;
        std::cout << "norm time : " << sum_time/(i+1)  << ",res :" << sum <<"\n";
    }

    return 0;

}

int thread_pool_demo_mat() {

    long num = 200000;
    long count = 10;

    std::vector<Mat66> values(num); // empty vector

    for(long i = 0; i < num; i++) {
        values[i].setRandom();
//        values[i].setOnes();
    }

    double t1,t2,sum_time = 0;

    for(int i = 0; i < count; i++) {
        Mat66 sum = Mat66::Zero();
        t1 = get_machine_timestamp_s();
        for(auto x : values) {
            sum += x;
        }
        t2 = get_machine_timestamp_s();
        sum_time += t2 - t1;
        if(i == count - 1)
            std::cout << "norm time : " << sum_time/(i+1)  << ",res :\n" << sum <<"\n";

    }


    std::cout << "para ........................." <<"\n";


    sum_time = 0;

    for(int i = 0; i < count; i++) {

        t1 = get_machine_timestamp_s();
        auto parallelResult = parallel_accumulate_mat(values.begin(), values.end(), Mat66::Zero().eval(),5000);
        t2 = get_machine_timestamp_s();
        sum_time += t2 - t1;
        if(i == count - 1)
            std::cout << "para time : " << sum_time/(i+1)  << ",res :\n" << parallelResult << std::flush <<"\n";
    }



    return 0;

}

