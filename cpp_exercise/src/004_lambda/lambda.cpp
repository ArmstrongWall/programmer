//
// Created by wzq on 18-10-16.
//
#include <functional>
#include <vector>

#include "lambda.h"

class Data {
public:
    Data()  = default;
    ~Data() = default;

    std::vector<int> a;
};

class A {

public:
    A()  = default;
    ~A() = default;

    std::vector<int> a;
    Data d;

    void la_de() {

        int b = 1;
        a.push_back(1);

        auto func1 = [data = std::move(a)]{
            std::cout << *data.begin() << "\n";
        };

        func1();

        std::cout << a.size();


    }


};


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

    A v;
    v.la_de();

}