//
// Created by wzq on 18-6-25.
//


// bind example
#include <iostream>     // std::cout
#include <functional>   // std::bind

// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide (double x, double y) {return x/y;}

struct MyPair {
    double a,b;
    double multiply() {return a*b;}
};

int bind () {
    using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

    // binding functions:
    auto fn_five = std::bind (my_divide,10,2);               // returns 10/2
    std::cout << fn_five() << '\n';                          // 5

    auto fn_half = std::bind (my_divide,_1,2);               // returns x/2
    std::cout << fn_half(10) << '\n';                        // 5

    auto fn_invert = std::bind (my_divide,_2,_1);            // returns y/x
    std::cout << fn_invert(10,2) << '\n';                    // 0.2

    auto fn_rounding = std::bind<int> (my_divide,_1,_2);     // returns int(x/y)
    std::cout << fn_rounding(10,3) << '\n';                  // 3

    MyPair ten_two {10,2};

    // binding members:
    auto bound_member_fn = std::bind (&MyPair::multiply,_1); // returns x.multiply()
    std::cout << bound_member_fn(ten_two) << '\n';           // 20

    auto bound_member_data = std::bind (&MyPair::a,ten_two); // returns ten_two.a
    std::cout << bound_member_data() << '\n';                // 10

    return 0;
}
