//
// Created by wzq on 18-10-20.
//

#include "condition_variable.h"
#define NUM 10
std::mutex	mut;
std::queue<int>	data_queue;		//	1
std::condition_variable	data_cond;
bool ready = false;
void process(const int &data) {
    std::cout << "process data = " << data << std::endl;
}

bool is_last_chunk(const int &data) {
    return (data == NUM - 1);
}

void data_preparation_thread()
{

    usleep(5000*1000);
    int count = 0;
    //while(true) {
        int	const data = count;
        std::lock_guard<std::mutex>	lk(mut);
        data_queue.push(data);		//	2
        std::cout << "push data = " << data << std::endl;
        ready = true;
        data_cond.notify_one();		//	3
        count++;
//        if(count > NUM)
//            break;

    //}
}


void data_processing_thread() {
    //while(true) {
        std::unique_lock<std::mutex> lk(mut);		//	4
        data_cond.wait(
                lk,[]{return ready;});		//	5
        int	data=data_queue.front();
    std::cout << "pop data = " << data << std::endl;

    data_queue.pop();
        lk.unlock();		//	6
        process(data);
//        if(is_last_chunk(data))
//            break;
        usleep(20*1000);
    //}
}


void condition_variable_demo(){
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);

    t1.join();
    t2.join();
}


