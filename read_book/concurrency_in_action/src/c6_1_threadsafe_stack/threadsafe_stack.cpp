//
// Created by wzq on 18-10-21.
//

#include "threadsafe_stack.h"

#define NUM 100

threadsafe_stack<int> threadsafe_data_stack;		//	1

void threadsafe_stack_process(const int &data) {
    std::cout << "process data = " << data << std::endl;
}

bool threadsafe_stack_is_last_chunk(const int &data) {
    return (data == 0);
}

void threadsafe_stack_data_preparation_thread() {
    int count = 0;
    while(true) {
        int	const data = count;
        threadsafe_data_stack.push(data);		//	2
        std::cout << "push data = " << data << std::endl;
        count++;
        if(count > NUM)
            break;
        usleep(5*1000);
    }
}

void threadsafe_stack_data_processing_thread() {
    while(true) {
        int	data;
        threadsafe_data_stack.pop(data);
        threadsafe_stack_process(data);
        if(threadsafe_stack_is_last_chunk(data))
            break;
        usleep(5*1000);
    }
}

void threadsafe_stack_demo(){
    std::thread t1(threadsafe_stack_data_preparation_thread);
    sleep(2);

    std::thread t2(threadsafe_stack_data_processing_thread);

    t1.join();
    t2.join();
}