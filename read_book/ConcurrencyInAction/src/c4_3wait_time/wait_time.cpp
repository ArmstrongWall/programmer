//
// Created by wzq on 18-6-25.
//

#include "wait_time.h"

InsPub::InsPub():run_(true) {
    thread_ins_pub = std::thread(&InsPub::ins_pub_thread,this);
}
InsPub::~InsPub() {
    if(thread_ins_pub.joinable())
    {
        thread_ins_pub.join();
    }
}

void InsPub::ins_pub_thread() {

    while(run_) {
        auto start = std::chrono::system_clock::now();

        sleep(1);

        auto end   = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<chrono::microseconds>(end - start);

        std::cout<< duration.count() <<std::endl;
    }
}