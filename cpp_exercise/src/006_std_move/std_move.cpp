//
// Created by wzq on 18-10-21.
//

#include "std_move.h"

void std_move_demo() {
    std::string str = "Hello";
    std::vector<std::string> v;

    // 使用 push_back(const T&) 重载，
    // 表示我们将带来复制 str 的成本
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";

    // 使用右值引用 push_back(T&&) 重载，
    // 表示不复制字符串；而是
    // str 的内容被移动进 vector
    // 这个开销比较低，但也意味着 str 现在可能为空。
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";

    std::cout << "The contents of the vector are \"" << v[0]
              << "\", \"" << v[1] << "\"\n";
}

