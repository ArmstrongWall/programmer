//
// Created by johnny on 2/5/18.
//
#include "RAIIWaitForThread.h"

planControl::planControl(bool t):keepPlanControl(t)
{
    thread_planControl = std::thread(&planControl::planControlThreadLoop,this);
    cout << "con finish" << endl;
}

planControl::~planControl()
{
    if(thread_planControl.joinable())
    {
        thread_planControl.join();
    }
}


void planControl::planControlThreadLoop()
{

    while(keepPlanControl)
    {
        cout << "planLoop"<<i << endl;
        i++;
        sleep(1);
        //(i>100)
            //break;
    }
}

void planControl::send() {
    cout << "send" << endl;
}