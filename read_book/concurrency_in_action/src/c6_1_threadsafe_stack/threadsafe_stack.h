//
// Created by wzq on 18-10-21.
//

#ifndef CONCURRENCY_IN_ACTION_THREADSAFE_STACK_H
#define CONCURRENCY_IN_ACTION_THREADSAFE_STACK_H

#include <exception>
#include <thread>
#include <queue>
#include <mutex>
#include <stack>
#include <iostream>
#include <condition_variable>
#include <zconf.h>

struct	empty_stack:	std::exception
{
    const	char*	what()	const	throw()	{
        return	"empty	stack!";
    };
};

template<typename	T>
class	threadsafe_stack
{
private:
    std::stack<T>	data;
    mutable	std::mutex	m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const	threadsafe_stack&	other)
    {
        std::lock_guard<std::mutex>	lock(other.m);
        data=other.data;
    }
    threadsafe_stack&	operator=(const	threadsafe_stack&)	=	delete;
    void	push(T	new_value)
    {
        std::lock_guard<std::mutex>	lock(m);
        data.push(std::move(new_value));		//	1
    }
    std::shared_ptr<T>	pop()
    {
        std::lock_guard<std::mutex>	lock(m);
        if(data.empty())	throw	empty_stack();		//	2
        std::shared_ptr<T>	const	res(
                std::make_shared<T>(std::move(data.top())));		//	3
        data.pop();		//	4
        return	res;
    }
    void	pop(T&	value)
    {
        std::lock_guard<std::mutex>	lock(m);
        if(data.empty())	throw	empty_stack();
        value=std::move(data.top());		//	5
        data.pop();		//	6
    }
    bool	empty()	const
    {
        std::lock_guard<std::mutex>	lock(m);
        return	data.empty();
    }
};
void threadsafe_stack_demo();
#endif //CONCURRENCY_IN_ACTION_THREADSAFE_STACK_H
