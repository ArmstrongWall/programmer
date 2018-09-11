#include <iostream>
#include "a.h"
#include "b.h"


int main() {

    auto a = new A;
    auto b = new B(a);

    b->self_print();
    b->call_a_print();
    b->pA->self_print();
    b->pA->call_b_print();



    return 0;
}