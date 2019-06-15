//
// Created by johnny on 6/15/19.
//
#include <stack>
#include <climits>
#include "min_stack.h"

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    std::stack<int> num_stack;
    std::stack<int> min_stack;

    int min = INT_MAX;

    void push(int x) {
        num_stack.push(x);
        if(x <= min) {
            min = x;
        }
        min_stack.push(min);
    }

    void pop() {
        num_stack.pop();
        min_stack.pop();
        if(min_stack.empty()) {
            min = INT_MAX;
        } else {
            min = min_stack.top();
        }
    }

    int top() {
        return num_stack.top();
    }

    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */