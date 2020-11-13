//
// Created by wzq on 18-10-20.
//

#include "unprotected_mutex.h"

some_data*	unprotected;
data_wrapper unprotected_mutex_x;

void	malicious_function(some_data&	protected_data)
{
    unprotected=&protected_data;
}

void	unprotected_mutex_demo()
{
    unprotected_mutex_x.process_data(malicious_function);				//	2	传递一个恶意函数
    unprotected->do_something();				//	3	在无保护的情况下访问保护数据
}