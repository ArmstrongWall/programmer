//
// Created by wzq on 18-9-11.
//

#ifndef INC_016_MUTUAL_CLASS_B_H
#define INC_016_MUTUAL_CLASS_B_H
#include <iostream>
#include "a.h"

class A;

class B{
public:
    B() = default;
    explicit B(A *pa):pA(pa){};
    ~B() = default;
    void self_print(){
        std::cout << "I'm B" << std::endl;
    }
    void call_a_print();

    A* pA;
};

#endif //INC_016_MUTUAL_CLASS_B_H
