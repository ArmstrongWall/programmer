//
// Created by johnny on 6/15/19.
//

//232. 用栈实现队列
//https://leetcode-cn.com/problems/implement-queue-using-stacks/
//        请你仅使用两个栈实现先入先出队列。队列应当支持一般队列的支持的所有操作（push、pop、peek、empty）：
//
//实现 MyQueue 类：
//
//void push(int x) 将元素 x 推到队列的末尾
//int pop() 从队列的开头移除并返回元素
//int peek() 返回队列开头的元素
//        boolean empty() 如果队列为空，返回 true ；否则，返回 false
//
//
//
//说明：
//
//你只能使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
//你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
//
//
//
//进阶：
//
//你能否实现每个操作均摊时间复杂度为 O(1) 的队列？换句话说，执行 n 个操作的总时间复杂度为 O(n) ，即使其中一个操作可能花费较长时间。
//
//
//
//示例：
//
//输入：
//["MyQueue", "push", "push", "peek", "pop", "empty"]
//[[], [1], [2], [], [], []]
//输出：
//[null, null, null, 1, 1, false]
//
//解释：
//MyQueue myQueue = new MyQueue();
//myQueue.push(1); // queue is: [1]
//myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
//myQueue.peek(); // return 1
//myQueue.pop(); // return 1, queue is [2]
//myQueue.empty(); // return false
//
//
//
//提示：
//
//1 <= x <= 9
//最多调用 100 次 push、pop、peek 和 empty
//        假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）
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