//
// Created by johnny on 2/5/18.
//
#include <iostream>
#include <thread>
#include <sys/time.h>
#include <cmath>
using namespace std;

void hello(){
    while(true) {
        struct  timeval  time_start;
        gettimeofday(&time_start,NULL);
        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
        cout <<"hello time " <<  cost_time << endl;
    }

}

void hello2(){
    while(true) {
        struct  timeval  time_start;
        gettimeofday(&time_start,NULL);
        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
        cout <<"hello2 time " <<  cost_time << endl;
    }

}

void demo() {

    cout.setf(ios::fixed);
    float idepth = (rand() % 100001);// / 100000.0f ;
    float second_best_match_err = NAN;
    std::cout << second_best_match_err << std::endl;

//    cout.setf(ios::fixed);
//    std::cout << "Hello, World!" << std::endl;
//
//    std::thread t(hello);
//    std::thread t2(hello2);
//
//    t2.join();
//
//    cout <<"main time "  << endl;
//
//    t.join();
//
//
//
//    while(true) {
//        struct  timeval  time_start;
//        gettimeofday(&time_start,NULL);
//        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
//        cout <<"main time " <<  cost_time << endl;
//    }

}
