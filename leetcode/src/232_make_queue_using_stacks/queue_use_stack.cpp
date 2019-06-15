//
// Created by johnny on 6/15/19.
//
#include <stack>
#include <iostream>
#include "queue_use_stack.h"

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    std::stack<int> main_stack;

    /** Push element x to the back of queue. */
    void push(int x) {
        main_stack.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        std::stack<int> temp_stack;
        int pop_value = 0;
        while (!main_stack.empty()) {
            if(main_stack.size() == 1) {
                pop_value = main_stack.top();
                main_stack.pop();
                break;
            }
            temp_stack.push(main_stack.top());
            main_stack.pop();
        }
        while (!temp_stack.empty()) {
            main_stack.push(temp_stack.top());
            temp_stack.pop();
        }

        return pop_value;
    }

    /** Get the front element. */
    int peek() {
        std::stack<int> temp_stack;
        int peek_value = 0;
        while (!main_stack.empty()) {
            if(main_stack.size() == 1) {
                peek_value = main_stack.top();
            }
            temp_stack.push(main_stack.top());
            main_stack.pop();
        }
        while (!temp_stack.empty()) {
            main_stack.push(temp_stack.top());
            temp_stack.pop();
        }

        return peek_value;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return main_stack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

void My_queue() {

    MyQueue* obj = new MyQueue();
    obj->push(1);

    int param_2 = obj->pop();
    std::cout << "pop : "<< param_2;

//    int param_3 = obj->top();
//    std::cout << "top : "<< param_3;


    bool param_4 = obj->empty();

}