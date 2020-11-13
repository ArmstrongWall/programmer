//
// Created by wzq on 2020/11/11.
//

#ifndef LEETCODE_STRING_H
#define LEETCODE_STRING_H

class String {
    String(const char* s = nullptr);
    String(const String &other);
    ~String();
    String operator=(const String&other);
};

#endif //LEETCODE_STRING_H
