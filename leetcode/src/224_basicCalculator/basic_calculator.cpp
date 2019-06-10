//
// Created by johnny on 6/9/19.
//

#include <string>
#include <stack>
#include <iostream>
#include "basic_calculator.h"


class Solution {
public:


    int calculate(std::string s) {
        enum {STATE_BEGIN = 0, STATE_NUMBER, STATE_OPERATION};
        std::stack<int>   num_stack;
        std::stack<char>  operator_stack;
        bool              compute_flag  = false;
        int               state         = STATE_BEGIN;
        int               number        = 0;

        for(int i = 0; i < s.length(); i++) {
            if(s[i] == ' ') {
                continue;
            }
            switch (state) {
                case STATE_BEGIN : {
                    if(s[i] >= '0' && s[i] <= '9') { // 数字的情况
                        state = STATE_NUMBER;
                    } else if(s[i] == '(') {
                        state = STATE_OPERATION;
                    }
                    i--;
                    break;
                }


                case STATE_NUMBER : {
                    if(s[i] >= '0' && s[i] <= '9') { // 数字的情况
                        number = number * 10 + s[i] - '0';
                    }  else {
                        num_stack.push(number);
                        number = 0;
                        if(compute_flag) {
                            compute(num_stack,operator_stack);
                        }
                        state = STATE_OPERATION;
                        i--;
                    }

                    break;
                }

                case STATE_OPERATION : {
                    if(s[i] == '+' || s[i] == '-') { // 符号的情况
                        operator_stack.push(s[i]);
                        compute_flag = true;
                    } else if(s[i] >= '0' && s[i] <= '9') {
                        state = STATE_NUMBER;
                        i--;
                    }

                    break;
                }

            }
        }

        if(compute_flag) {
            num_stack.push(number);
            compute(num_stack,operator_stack);
        }

        return num_stack.top();

    }

    void compute(std::stack<int>& num_stack, std::stack<char>& operator_stack) {
        if(num_stack.size() < 2 || operator_stack.empty()) {
            return;
        } else {
            int a = num_stack.top();
            num_stack.pop();
            int b = num_stack.top();
            num_stack.pop();
            if(operator_stack.top() == '+') {
                num_stack.push(a+b);
            } else if(operator_stack.top() == '-') {
                num_stack.push(a-b);
            }
            operator_stack.pop();
        }
    }
};

int basic_calculator() {
    std::string s = "1+121  ";
    Solution solve;
    std::cout << "result is " << solve.calculate(s) ;

}