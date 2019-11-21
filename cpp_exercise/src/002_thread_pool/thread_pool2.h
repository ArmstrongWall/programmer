/**
 * Copyright© 2016-2018. UISEE (SHANGHAI) AUTOMOTIVE TECHNOLOGIES LTD. All rights reserved.
 * LICENSE AGREEMENT
 * The copy of the SOFTWARE is licensed, not sold.
 * Customer owns any media on which the SOFTWARE is recorded, but UISEE and its licensors or
 * suppliers retain ownership of the copy of the SOFTWARE itself, including all copyrights and
 * other intellectual property rights in and to the SOFTWARE (including but not limited to all
 * images, photographs, animations, video, audio, music, text, and other information incorporated
 * into the SOFTWARE), the accompanying printed materials, and any copies of the SOFTWARE.
 * The SOFTWARE is protected by copyright laws and international treaty provisions. Accordingly,
 * Customer is required to treat the SOFTWARE like any other copyrighted material,except as
 * otherwise allowed pursuant to this AGREEMENT and that it may make one copy of the SOFTWARE
 * solely for backup or archive purposes, provided that Customer reproduces all copyright and
 * proprietary notices that are on the original copy. The algorithms, structure, organization
 * and source code of the SOFTWARE are the valuable trade secrets and confidential
 * information of UISEE. Except as otherwise expressly provided herein, neither this AGREEMENT
 * nor UISEE grants Customer any express or implied right under any UISEE patents, copyrights,
 * trademarks, or other intellectual property rights in the SOFTWARE, and all rights, title
 * and interest in and to the SOFTWARE not expressly granted are reserved by UISEE or its
 * licensors or suppliers.
 *
 * @file   thread_pool2.h
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-11-21
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-11-21    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#ifndef CPP_EXERCISE_THREAD_POOL2_H
#define CPP_EXERCISE_THREAD_POOL2_H

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
        :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
                [this]
                {
                    for(;;)
                    {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this]{ return this->stop || !this->tasks.empty(); });
                            if(this->stop && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        task();
                    }
                }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}


int thread_pool_demo();

#endif


#endif //CPP_EXERCISE_THREAD_POOL2_H
