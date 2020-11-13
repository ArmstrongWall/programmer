//
// Created by johnny on 6/10/19.
//
#include <queue>
#include <iostream>

#include "stack_use_queue.h"

//225. 用队列实现栈
//https://leetcode-cn.com/problems/implement-stack-using-queues/
//        使用队列实现栈的下列操作：
//
//push(x) -- 元素 x 入栈
//pop() -- 移除栈顶元素
//top() -- 获取栈顶元素
//empty() -- 返回栈是否为空
//
//        注意:
//
//你只能使用队列的基本操作-- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
//你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
//你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。
//


class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    std::queue<int> main_queue;

    /** Push element x onto stack. */
    void push(int x) {
        main_queue.push(x);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        std::queue<int> temp_queue;
        int pop_value = 0;
        while (!main_queue.empty()) {
            if(main_queue.size() == 1) {
                pop_value = main_queue.front();
                main_queue.pop();

                break;
            }
            temp_queue.push(main_queue.front());
            main_queue.pop();

        }
        while (!temp_queue.empty()) {
            main_queue.push(temp_queue.front());
            temp_queue.pop();
        }

        return pop_value;
    }

    /** Get the top element. */
    int top() {
        return main_queue.back();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return main_queue.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

void My_Stack() {

    MyStack* obj = new MyStack();
    obj->push(1);

    int param_2 = obj->pop();
    std::cout << "pop : "<< param_2;

//    int param_3 = obj->top();
//    std::cout << "top : "<< param_3;


    bool param_4 = obj->empty();

}