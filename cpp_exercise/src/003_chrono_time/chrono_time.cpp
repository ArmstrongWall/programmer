//
// Created by wzq on 18-10-16.
//

#include "chrono_time.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <iostream>
#include <iomanip>

std::chrono::time_point<std::chrono::system_clock> lasttime = std::chrono::system_clock::now();
int time() {

    bool run = true;
    while(run) {
        std::chrono::time_point<std::chrono::system_clock,std::chrono::microseconds> tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        auto tmp=std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
        std::time_t timestamp = tmp.count();
        //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
        std::cout <<"now timestamp: " << std::setiosflags(std::ios::fixed) << std::setprecision(8) << (static_cast<double>(timestamp))/1000000.0  <<std::endl;

        auto nowtime = std::chrono::system_clock::now();
        std::cout<<"thread cost time: "<< std::chrono::duration_cast<std::chrono::microseconds>(nowtime - lasttime).count() <<" us "<< std::endl;

        {
            std::cout<<"doing somethings ... " << std::endl;
        }


        lasttime = std::chrono::system_clock::now();
    }
    return 0;
}

