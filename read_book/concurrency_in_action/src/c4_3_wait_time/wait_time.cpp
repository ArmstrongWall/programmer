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

    std::chrono::microseconds period(5000);
    while(run_) {


        auto start = std::chrono::system_clock::now();

        usleep(2000);

        auto end   = std::chrono::system_clock::now();

        auto elapse  = std::chrono::duration_cast<chrono::microseconds>(end - start);

        if (period > elapse) {
            std::this_thread::sleep_for(period - elapse);
        } else {
            std::cout << "Too much time for calculation: " << elapse.count() << std::endl;
        }

        auto end2   = std::chrono::system_clock::now();
        std::cout<<"thread cost time: "<< std::chrono::duration_cast<chrono::microseconds>(end2 - start).count() <<std::endl;
    }
}

void wait_time(){

    InsPub *pub;
    pub = new InsPub();

    int i=1;
    while(i)
    {
        i++;
        sleep(1);
    }
}
