/**
 * @file    ThreadPool.h
 * @brief   this file define a thread pool,
 *          when you wait to use it, please use the c++11 standard
 *          what's more, don't forget to add Link flag "-Wl,--no-as-needed"
 *
 * @note    it is easy to use
 *          first you should define work functions, the format must be void(*)(void*),
 *          you can also define a function object to use
 *          and then, please define your thread pool, the format is like
 *          "ThreadPool<DataType> threads(threadNum);" or "ThreadPool<DataType*> threads(threadNum);"
 *          be attention: void is forbidden
 *          the two types of pre-define have some difference
 *          the former is used for one object, the latter is used for object array,
 *          and next, you can call threads.reduce(numth, workFunction, Data) to call the workFunction
 *          in numth thread
 *          at last, if you should know if the thread is Synchronize, call threads.isSynchronize()
 *
 * @example
 * in this example, you can print each value of data
 *
 *            void workFunc1(void* data_) {
 *                double data = *data_;
 *                printf("data = %lf\n", data);
 *            }
 *
 *            double data1[12];
 *            ThreadPool<double> threads1(12);
 *            for(int i = 0; i < 12; ++i)
 *                threads.reduce(i, workFunc1, data1[i]);
 *
 * in next example, you can work with a chunk of data
 *
 *          #define ROW 12
 *          #define COL 24
 *          void workFunc2(void*data_) {
 *              double *data = (double*)data_;
 *              for(int i = 0; i < COL; ++i)
 *                  deal(data[i]);
 *          }
 *
 *          double data2[ROW][COL];
 *          ThreadPool<double*> threads2(ROW);
 *          for(int i = 0; i < 12; ++i)
 *              threads2.reduce(i, workFunc2, data2[i]);
 *
 * @author  lancelot
 * @date    20160727
 * @Email  3128243880@qq.com
 * @version 1.3
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <stdio.h>

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace thread_pool {

template<typename T> struct Trait {
    typedef  T                 typeName;
    typedef  T*                pointer;
    typedef  T&                reference;
    typedef const  T*          const_pointer;
    typedef const  T&          const_reference;
};

template <typename T> void defaultFunc(void *) {}

template <typename T>
class ThreadPool
{
public:
    enum {
        WorkThreadNum = 4
    };

public:
    typedef std::function<void(void*)> WorkFunc;

public:
    ThreadPool(int threadNum = 0) {
        maxThreadNum   = threadNum > WorkThreadNum ? threadNum : WorkThreadNum;
        //at least 6 thread in pool

        workFunc       = new WorkFunc[maxThreadNum];
        running        = new bool[maxThreadNum];
        threads        = new std::thread[maxThreadNum];
        Mutex          = new std::mutex[maxThreadNum];
        conditionVal   = new std::condition_variable[maxThreadNum];
        x              = new T[maxThreadNum];
        sourceMutex    = new std::mutex[maxThreadNum];
        sleepThreadNum = maxThreadNum;

        for(int i = 0; i < maxThreadNum; ++i) {
            workFunc[i] = defaultFunc<T>;
            running[i] = false;
            threads[i] = std::thread(&ThreadPool::workLoop, this, i);
        }
    }

    ~ThreadPool() {
        while(!isSynchronize());
        delete[]workFunc;
        delete[]running;
        delete[]threads;
        delete[]Mutex;
        delete[]conditionVal;
        delete[]x;
        delete[]sourceMutex;
    }

    bool reduce(int idx, WorkFunc f, typename Trait<T>::reference x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;

        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = f;
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }

    bool isSynchronize() {
        return sleepThreadNum == maxThreadNum;
    }

    template<class U>
    bool reduce(int idx, void (U::*f)(void*) , U* p, typename Trait<T>::reference x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;

        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = std::bind(f, p, std::placeholders::_1);
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }

    template<class U>
    bool reduce(int idx, void (U::*f)(void*) , typename Trait<T>::reference x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;

        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = std::bind(f, std::placeholders::_1);
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }


private:
    void workLoop(int idx) {
        std::unique_lock<std::mutex> lock(Mutex[idx]);
        while(true)
        {
            if(running[idx] == false)
                conditionVal[idx].wait(lock);

            workFunc[idx]((void*)&x[idx]);
            ++sleepThreadNum;
            workFunc[idx] = defaultFunc<T>;
            running[idx] = false;
        }
    }


private:
    ////////////////////////////////////////////
    /// \brief thread manager
    ////////////////////////////////////////////
    std::condition_variable *conditionVal;
    std::mutex              *Mutex;
    std::thread             *threads;
    int                     maxThreadNum;
    std::atomic_int         sleepThreadNum;


    /////////////////////////////////////////
    /// \brief workFunc param
    /////////////////////////////////////////
    WorkFunc    *workFunc;
    T           *x;
    bool        *running;
    std::mutex  *sourceMutex;
};


template <typename T>
class ThreadPool<T*>
{
public:
    typedef typename Trait<T>::const_pointer    const_pointer;
    typedef typename Trait<T>::const_reference  const_reference;
    typedef typename Trait<T>::pointer          pointer;
    typedef typename Trait<T>::reference        reference;
    typedef typename Trait<T>::typeName         typeName;

public:
    enum {
        WorkThreadNum = 4
    };

public:
    typedef std::function<void(void*)> WorkFunc;

public:
    ThreadPool(int threadNum = 0) {
        maxThreadNum   = threadNum > WorkThreadNum ? threadNum : WorkThreadNum;

        workFunc       = new WorkFunc[maxThreadNum];
        running        = new bool[maxThreadNum];
        threads        = new std::thread[maxThreadNum];
        Mutex          = new std::mutex[maxThreadNum];
        conditionVal   = new std::condition_variable[maxThreadNum];
        x              = new pointer[maxThreadNum];
        sourceMutex    = new std::mutex[maxThreadNum];

        sleepThreadNum = maxThreadNum;

        for(int i = 0; i < maxThreadNum; ++i) {
            workFunc[i] = defaultFunc<typeName>;
            running[i] = false;
            threads[i] = std::thread(&ThreadPool::workLoop, this, i);
        }
    }

    ~ThreadPool() {
        while(!isSynchronize());
        delete[]workFunc;
        delete[]running;
        delete[]threads;
        delete[]Mutex;
        delete[]conditionVal;
        delete[]x;
        delete[]sourceMutex;
    }

    bool reduce(int idx, WorkFunc f, pointer x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;
        
        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = f;
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }

    template<class U>
    bool reduce(int idx, void (U::*f)(void*) , U* p, pointer x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;

        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = std::bind(f, p, std::placeholders::_1);
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }

    template<class U>
    bool reduce(int idx, void (U::*f)(void*) , pointer x) {
        if(idx < 0 || idx >= maxThreadNum)
            return false;

        sourceMutex[idx].lock();
        --sleepThreadNum;
        workFunc[idx] = std::bind(f, std::placeholders::_1);
        this->x[idx] = x;
        running[idx] = true;
        sourceMutex[idx].unlock();

        conditionVal[idx].notify_all();
        return true;
    }


    bool isSynchronize() {
        return sleepThreadNum == maxThreadNum;
    }

private:
    void workLoop(int idx) {
        std::unique_lock<std::mutex> lock(Mutex[idx]);
        while(true)
        {
            if(running[idx] == false)
                conditionVal[idx].wait(lock);

            workFunc[idx]((void*)x[idx]);
            ++sleepThreadNum;
            workFunc[idx] = defaultFunc<T>;
            running[idx] = false;
        }
    }

private:
    ////////////////////////////////////////////
    /// \brief thread manager
    ////////////////////////////////////////////
    std::condition_variable *conditionVal;
    std::mutex              *Mutex;
    std::thread             *threads;
    int                     maxThreadNum;
    std::atomic_int         sleepThreadNum;

    /////////////////////////////////////////
    /// \brief workFunc param
    /////////////////////////////////////////
    WorkFunc    *workFunc;
    pointer     *x;
    bool        *running;
    std::mutex  *sourceMutex;
};



} // end of namespace pi

#endif // THREADPOOL_H

