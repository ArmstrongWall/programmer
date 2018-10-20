//
// Created by wzq on 18-10-20.
//

#include "threadsafe_queue.h"
#define NUM 10000

threadsafe_queue<int> threadsafe_data_queue;		//	1

void threadsafe_queue_process(const int &data) {
    std::cout << "process data = " << data << std::endl;
}

bool threadsafe_queue_is_last_chunk(const int &data) {
    return (data == NUM - 1);
}

void threadsafe_queue_data_preparation_thread() {
    int count = 0;
    while(true) {
        int	const data = count;
        threadsafe_data_queue.push(data);		//	2
        std::cout << "push data = " << data << std::endl;
        count++;
        if(count > NUM)
            break;
        usleep(5*1000);
    }
}

void threadsafe_queue_data_processing_thread() {
    while(true) {
        int	data;
        threadsafe_data_queue.wait_and_pop(data);
        threadsafe_queue_process(data);
        if(threadsafe_queue_is_last_chunk(data))
            break;
        usleep(6*1000);
    }
}

void threadsafe_queue_demo(){
    std::thread t1(threadsafe_queue_data_preparation_thread);
    std::thread t2(threadsafe_queue_data_processing_thread);

    t1.join();
    t2.join();
}