//
// Created by johnny on 2/5/18.
//

#ifndef CONCURRENCYINACTION_RAIIWAITFORTHREAD_H
#define CONCURRENCYINACTION_RAIIWAITFORTHREAD_H
#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;

class planControl{

public:
    planControl(bool t);
    ~planControl();
    planControl(planControl const&)= delete;
    planControl& operator= (planControl const&) = delete;
    void send();

private:
    std::thread thread_planControl;
    bool keepPlanControl;
    void planControlThreadLoop();
    int  i;

};

#endif //CONCURRENCYINACTION_RAIIWAITFORTHREAD_H
