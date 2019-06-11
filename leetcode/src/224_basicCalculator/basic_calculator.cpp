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
        std::stack<long>   num_stack;
        std::stack<char>  operator_stack;
        bool              compute_flag  = false;
        int               state         = STATE_BEGIN;
        long              number        = 0;

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
                    }  else { // 符号的情况
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
                    } else if(s[i] == '(') {
                        state = STATE_NUMBER;
                        compute_flag = false;
                    } else if(s[i] == ')') {
                        compute(num_stack,operator_stack);
                    }

                    break;
                }
                default: {

                }

            }
        }

        if(compute_flag) {
            if(number) {
                num_stack.push(number);
            }
            compute(num_stack,operator_stack);
        }

        return num_stack.top();

    }

private:
    void compute(std::stack<long>& num_stack, std::stack<char>& operator_stack) {
        if(num_stack.size() < 2 || operator_stack.empty()) {
            return;
        } else {
            int a = num_stack.top();
            num_stack.pop();
            int b = num_stack.top();
            num_stack.pop();
            if(operator_stack.top() == '+') {
                num_stack.push(b+a);
            } else if(operator_stack.top() == '-') {
                num_stack.push(b-a);
            }
            operator_stack.pop();
        }
    }
};

int basic_calculator() {
    std::string s = "(1+(4+5+2)-3)+(6+8)";
    Solution solve;
    std::cout << "result is " << solve.calculate(s) ;

}