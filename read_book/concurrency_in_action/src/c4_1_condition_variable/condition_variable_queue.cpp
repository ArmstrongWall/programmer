/**
  *
 * @file   condition_variable1.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-5-14
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-5-14    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#include "condition_variable.h"
#define NUM 10000
std::mutex	mut_queue;
std::queue<int>	data_queue_queue;		//	1
std::condition_variable	data_cond_queue;

void process_queue(const int &data) {
    std::cout << "process_queue data = " << data << std::endl;
}

bool is_last_chunk_queue(const int &data) {
    return (data == NUM - 1);
}

void data_preparation_thread_queue()
{
    int count = 0;
    while(true) {
        int	const data = count;
        std::lock_guard<std::mutex>	lk(mut_queue);
        data_queue_queue.push(data);		//	2
        std::cout << "push data = " << data << std::endl;
        data_cond_queue.notify_one();		//	3
        count++;
        if(count > NUM)
            break;
        usleep(5*1000);
    }
}


void data_processing_thread_queue() {
    while(true) {
        std::unique_lock<std::mutex> lk(mut_queue);		//	4
        data_cond_queue.wait(
                lk,[]{return !data_queue_queue.empty();});		//	5
        int	data=data_queue_queue.front();
        data_queue_queue.pop();
        lk.unlock();		//	6
        process_queue(data);
        if(is_last_chunk_queue(data))
            break;
        usleep(20*1000);
    }
}


void condition_variable_demo_queue(){
    std::thread t1(data_preparation_thread_queue);
    std::thread t2(data_processing_thread_queue);

    t1.join();
    t2.join();
}