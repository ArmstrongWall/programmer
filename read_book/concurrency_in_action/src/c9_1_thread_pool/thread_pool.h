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
 * @file   thread_pool.h
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

#ifndef CONCURRENCY_IN_ACTION_THREAD_POOL_H
#define CONCURRENCY_IN_ACTION_THREAD_POOL_H

#include <cassert>

#include<vector>
#include<thread>
#include<atomic>
#include<future>

#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>

class function_wrapper
{
    struct impl_base {
        virtual void call()=0;
        virtual ~impl_base() {}
    };
    std::unique_ptr<impl_base> impl;
    template<typename F>
    struct impl_type: impl_base
    {
        F f;
        impl_type(F&& f_): f(std::move(f_)) {}
        void call() { f(); }
    };
public:
    template<typename F>
    function_wrapper(F&& f):
            impl(new impl_type<F>(std::move(f)))
    {}

    void operator()() { impl->call(); }
    function_wrapper() = default;
    function_wrapper(function_wrapper&& other):
            impl(std::move(other.impl))
    {}
    function_wrapper& operator = (function_wrapper&& other)
    {
        impl = std::move(other.impl);
        return *this;
    }
    function_wrapper(const function_wrapper&) = delete;
    function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator=(const function_wrapper&)=delete;
};

class join_threads {
    std::vector<std::thread>& threads;
public:
    explicit join_threads(std::vector<std::thread>& threads_):threads(threads_) {}
    ~join_threads() {
        for(unsigned long i = 0;i<threads.size();++i) {
            if(threads[i].joinable())
                threads[i].join();
        }
    }
};

/**
* @class MPMCQueue
* @brief MPMCQueue to define a no lock ,threadsafe queue, use atomic operation to implement,
*        it is a multi Producer, multi Consumer threadsafe queue.
*/
template <typename T>
class MPMCQueue {
private:
    struct node;
    struct counted_node_ptr;
    struct node_counter;

    struct counted_node_ptr {
        int ref_count;
        node *ptr;
    };

    struct node_counter {
        unsigned internal_count : 30;
        unsigned external_counters : 2;
    };

    struct node {
        std::atomic<node_counter> count;
        std::atomic<counted_node_ptr> next;

        std::atomic<T*> data;

        node() : data(nullptr) {
            node_counter new_counter;
            new_counter.internal_count = 0;
            new_counter.external_counters = 2;
            count.store(new_counter);

            counted_node_ptr new_counted_node_ptr{ 0 };
            next.store(new_counted_node_ptr);
        }

        void release_ref() {
            node_counter old_counter = count.load(std::memory_order_relaxed);
            node_counter new_counter;
            do {
                new_counter = old_counter;
                --new_counter.internal_count;
            } while (!count.compare_exchange_strong(old_counter, new_counter, std::memory_order_acquire, std::memory_order_relaxed));

            if (!new_counter.internal_count && !new_counter.external_counters)
                delete this;
        }
    };

protected:
    std::atomic<counted_node_ptr> head, tail;

    static void increase_external_count(std::atomic<counted_node_ptr> &counter, counted_node_ptr &old_counter) {
        counted_node_ptr new_counter;
        do {
            new_counter = old_counter;
            ++new_counter.ref_count;
        } while (!counter.compare_exchange_strong(old_counter, new_counter, std::memory_order_acquire, std::memory_order_relaxed));

        old_counter.ref_count = new_counter.ref_count;
    }

    static void free_external_counter(counted_node_ptr &old_node_ptr) {
        node * const ptr = old_node_ptr.ptr;
        int count_increase = old_node_ptr.ref_count - 2;

        node_counter old_counter = ptr->count.load(std::memory_order_relaxed);
        node_counter new_counter;
        do {
            new_counter = old_counter;
            --new_counter.external_counters;
            new_counter.internal_count += count_increase;
        } while (!ptr->count.compare_exchange_strong(old_counter, new_counter, std::memory_order_acquire, std::memory_order_relaxed));

        if (!new_counter.internal_count && !new_counter.external_counters)
            delete ptr;
    }

    void set_new_tail(counted_node_ptr &old_tail, counted_node_ptr const &new_tail) {
        node * const current_tail_ptr = old_tail.ptr;
        while (!tail.compare_exchange_weak(old_tail, new_tail) && old_tail.ptr == current_tail_ptr);

        old_tail.ptr == current_tail_ptr ?
        free_external_counter(old_tail) :
        current_tail_ptr->release_ref();
    }

public:
    MPMCQueue() {
        counted_node_ptr new_counted_node;
        new_counted_node.ref_count = 1;
        new_counted_node.ptr = new node;

        head.store(new_counted_node);
        tail.store(new_counted_node);

        assert(head.is_lock_free() && "head/tail not lock free!");
        assert(new_counted_node.ptr->count.is_lock_free() && "count not lock free!");
        assert(new_counted_node.ptr->next.is_lock_free() && "next not lock free!");
    }
    ~MPMCQueue() {
        while (pop() != nullptr);
        delete head.load().ptr;
    }

    MPMCQueue(const MPMCQueue &q) = delete;
    MPMCQueue& operator=(const MPMCQueue &q) = delete;

    std::unique_ptr<T> pop() {
        counted_node_ptr old_head = head.load(std::memory_order_relaxed);
        for (;;) {
            increase_external_count(head, old_head);
            node * const ptr = old_head.ptr;
            if (ptr == tail.load().ptr)
                return nullptr;

            counted_node_ptr next = ptr->next.load();
            if (head.compare_exchange_strong(old_head, next)) {
                T * const res = ptr->data.exchange(nullptr);
                free_external_counter(old_head);
                return std::unique_ptr<T>(res);
            }

            ptr->release_ref();
        }
    }

    //! 尝试从队列中弹出数据,总会直接返回(当有失败时),即使没有值可检索;
    bool try_pop(T& value) {
        counted_node_ptr old_head = head.load(std::memory_order_relaxed);
        for (;;) {
            increase_external_count(head, old_head);
            node * const ptr = old_head.ptr;
            if (ptr == tail.load().ptr)
                return false;

            counted_node_ptr next = ptr->next.load();
            if (head.compare_exchange_strong(old_head, next)) {
                T * const res = ptr->data.exchange(nullptr);
                free_external_counter(old_head);
                value = std::move(*res);
                return true;
            }

            ptr->release_ref();
        }
    }

    void push(T &&new_value) {
        std::unique_ptr<T> new_data(new T(std::move(new_value)));
        counted_node_ptr new_next;
        new_next.ptr = new node;
        new_next.ref_count = 1;
        counted_node_ptr old_tail = tail.load();
        for (;;) {
            increase_external_count(tail, old_tail);
            T* old_data = nullptr;
            if (old_tail.ptr->data.compare_exchange_strong(old_data, new_data.get())) {
                counted_node_ptr old_next = { 0 };
                auto oldnexta = old_tail.ptr->next.load();
                if (!old_tail.ptr->next.compare_exchange_strong(old_next, new_next)) {
                    delete new_next.ptr;
                    new_next = old_next;
                }
                set_new_tail(old_tail, new_next);
                new_data.release();
                break;
            }
            else {
                counted_node_ptr old_next = { 0 };
                if (old_tail.ptr->next.compare_exchange_strong(old_next, new_next)) {
                    old_next = new_next;
                    new_next.ptr = new node;
                }
                set_new_tail(old_tail, old_next);
            }
        }
    }
};


template<typename T>
class threadsafe_lock_queue {
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node* tail;
    std::condition_variable data_cond;

    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head()
    {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [&] {return head != get_tail(); });
        return std::move(head_lock);
    }

    std::unique_ptr<node> wait_pop_head()
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<node> wait_pop_head(T& value)
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if (head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head(T& value)
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if (head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        value = std::move(*head->data);
        return pop_head();
    }

public:
    threadsafe_lock_queue() :
            head(new node), tail(head.get())
    {}
    threadsafe_lock_queue(const threadsafe_lock_queue& other) = delete;
    threadsafe_lock_queue& operator=(const threadsafe_lock_queue& other) = delete;

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data;
    }

    void wait_and_pop(T& value)
    {
        std::unique_ptr<node> const old_head = wait_pop_head(value);
    }

    void push(T new_value)
    {
        std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            node* const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }
        data_cond.notify_one();
    }

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> const old_head = try_pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    bool try_pop(T& value)
    {
        std::unique_ptr<node> const old_head = try_pop_head(value);
        return old_head != nullptr;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        return (head.get() == get_tail());
    }
};


class thread_pool {
    std::atomic_bool done;
//    threadsafe_lock_queue<function_wrapper> work_queue;
    MPMCQueue<function_wrapper> work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void worker_thread() {
        while(!done) {
            function_wrapper task;
            if(work_queue.try_pop(task)) {
                task();
            }
            else {
                std::this_thread::yield();
            }
        }
    }
public:
    thread_pool():
            done(false),joiner(threads) {

        unsigned const thread_count=std::thread::hardware_concurrency();

        try {
            for(unsigned i=0;i<thread_count;++i) {
                threads.emplace_back(
                        std::thread(&thread_pool::worker_thread,this));
            }
        }
        catch(...) {
            done = true;
            throw;
        }

    }

    ~thread_pool() {
        done = true;
    }

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) {
        typedef typename std::result_of<FunctionType()>::type result_type;
        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        work_queue.push(std::move(task));
        return res;
    }
};

int thread_pool_demo();
int thread_pool_demo_mat();

#endif //CONCURRENCY_IN_ACTION_THREAD_POOL_H
