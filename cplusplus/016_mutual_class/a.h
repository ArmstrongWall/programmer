//
// Created by wzq on 18-9-11.
//

#ifndef INC_016_MUTUAL_CLASS_A_H
#define INC_016_MUTUAL_CLASS_A_H
#include <iostream>
#include "b.h"

class B;

class A{
public:
    A() = default;
    explicit A(B *pb):pB(pb){};
    ~A() = default;
    void self_print(){
        std::cout << "I'm A" << std::endl;
    }
    void call_b_print();
    B* pB;
};

#endif //INC_016_MUTUAL_CLASS_A_H
