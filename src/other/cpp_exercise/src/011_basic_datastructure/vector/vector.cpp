/**
 * @file   vector.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-4-28
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-4-28    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#include "vector.h"

#include<iostream>
#include<vector>

int vector_assign() {
    std::vector<int> A(3,100);
    std::vector<int> B(5,200);
    A.assign(B.begin(),B.end());
    int i;
    for(auto a : A) {
        std::cout<<a<<std::endl;
    }

    std::cout<<"B begin"<<std::endl;

    for(auto b : B) {
        std::cout<<b<<std::endl;
    }

    return 0;
}

// swap vectors


int vector_swap ()
{
    std::vector<int> foo ;   // three ints with a value of 100
    std::vector<int> bar (5,200);   // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n';

    return 0;
}
