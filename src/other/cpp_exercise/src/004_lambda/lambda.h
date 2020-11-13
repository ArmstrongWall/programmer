//
// Created by wzq on 18-10-16.
//

#ifndef CPP_EXERCISE_LAMBDA_H
#define CPP_EXERCISE_LAMBDA_H

#include <iostream>

class S {
private:
    int x = 0;
    void use( const int &a, const int &b){
        std::cout << a+b << std::endl;
    }

public:
    void f() {
        int i = 0;
        //  auto l1 = [i, x]{ use(i, x); };    // 错误： x 非变量
        auto l2 = [i, x=x , this]{ use(i, x); };  // OK ，复制捕获

        i = 1; x = 1;
        l2(); // 调用 use(0,0)

         auto l3 = [i, &x=x, this]{ use(i, x); }; // OK ，引用捕获
        i = 2; x = 2;
        l3(); // 调用 use(1,2)
    }

};


int lambda_demo();

#endif //CPP_EXERCISE_LAMBDA_H
