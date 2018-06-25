//
// Created by wzq on 18-6-25.
//

#ifndef CONCURRENCYINACTION_WAIT_TIME_H
#define CONCURRENCYINACTION_WAIT_TIME_H
#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;

class InsPub{

public:
    InsPub();
    ~InsPub();
    InsPub(InsPub const&)= delete;


private:
    std::thread thread_ins_pub;
    void ins_pub_thread();
    bool run_;

};
#endif //CONCURRENCYINACTION_WAIT_TIME_H
