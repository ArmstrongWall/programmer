//
// Created by wzq on 18-10-20.
//

#ifndef CONCURRENCYINACTION_UNPROTECTED_MUTEX_H
#define CONCURRENCYINACTION_UNPROTECTED_MUTEX_H

#include <iostream>
#include <mutex>

class	some_data
{
    int	a;
    std::string	b;
public:
    void	do_something(){
        std::cout << "do_something" << std::endl;
    }
};
class	data_wrapper
{
private:
    some_data	data;
    std::mutex	m;
public:
    template<typename	Function>
    void	process_data(Function	func)
    {
        std::lock_guard<std::mutex>	l(m);
        func(data);				//	1	传递“保护”数据给用户函数
    }
};

void	unprotected_mutex_demo();

#endif //CONCURRENCYINACTION_UNPROTECTED_MUTEX_H
