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

void RAIIWaitForThread(){
    //同样是析构时去join线程，为什么使用new去初始化planControl类不去delete，线程就在main结束后被停止，而使用智能指针和正常定义一个planControl类线程在main结束后仍然可以运行
    //因为不去delete就没有调用析构函数，程序就进不了while，主要还是因为只要构造线程结束后，那么线程就已经开始了，跟指针不指针没关系

    planControl *plancon1;
    plancon1 = new planControl(true);
    delete plancon1;

    auto plancon2 = make_shared<planControl>(true);


    planControl plancon3(true);


    int i = 1;
    while(i)
    {
        plancon2->send();
        i++;
        sleep(1);
    }
}