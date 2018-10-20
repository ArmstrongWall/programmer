//
// Created by wzq on 18-10-20.
//

#ifndef CONCURRENCYINACTION_THREADSAFE_QUEUE_H
#define CONCURRENCYINACTION_THREADSAFE_QUEUE_H
#include <thread>
#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <zconf.h>

template<typename T>
class threadsafe_queue {
private:
    mutable	std::mutex	mut; //	1	互斥量必须是可变的
    std::queue<T>	data_queue;
    std::condition_variable	data_cond;
public:
    threadsafe_queue() = default;
    threadsafe_queue(threadsafe_queue const& other) {
        std::lock_guard<std::mutex>	lk(other.mut);
        data_queue=other.data_queue;
    }
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;		//	不允许简单的赋值

    void push(T	new_value) {
        std::lock_guard<std::mutex>	lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    //! 尝试从队列中弹出数据,总会直接返回(当有失败时),即使没有值可检索;
    bool try_pop(T&	value) {
        std::lock_guard<std::mutex>	lk(mut);
        if(data_queue.empty())
            return	false;
        value=data_queue.front();
        data_queue.pop();
        return	true;
    }
    std::shared_ptr<T>	try_pop(){
        std::lock_guard<std::mutex>	lk(mut);
        if(data_queue.empty())
            return	std::shared_ptr<T>();
        std::shared_ptr<T>	res(std::make_shared<T>
                                          (data_queue.front()));
        data_queue.pop();
        return	res;
    }
    //! 将会等待有值可检索的时候才返回
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex>	lk(mut);
        data_cond.wait(lk,[this]{return	!data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T>	wait_and_pop() {
        std::unique_lock<std::mutex>	lk(mut);
        data_cond.wait(lk,[this]{return	!data_queue.empty();});
        std::shared_ptr<T>	res(std::make_shared<T>
                                          (data_queue.front()));
        data_queue.pop();
        return	res;
    }

    bool empty() const {
        std::lock_guard<std::mutex>	lk(mut);
        return	data_queue.empty();
    }
};

void threadsafe_queue_demo();

#endif //CONCURRENCYINACTION_THREADSAFE_QUEUE_H
