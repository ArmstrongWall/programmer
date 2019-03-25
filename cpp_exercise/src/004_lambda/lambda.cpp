//
// Created by wzq on 18-10-16.
//

#include "lambda.h"
#include <functional>



int lambda_demo(){

    auto func = [] () { std::cout << "Hello world"<< std::endl; };
    func(); // now call the function

    //传递参数
    auto func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';

    //值捕获
    int a = 2;
    auto func1 = [a]{ return a; };
    std::cout << "func1: " << func1() << '\n';

    //引用捕获
    auto func3 = [&a]{ return a; };
    std::cout << "func1: " << func3() << '\n';

    //传递参数and引用捕获
    auto func4 = [&a](int i){ return a+i; };
    std::cout << "func1: " << func4(4) << '\n';

    S s;
    s.f();

}