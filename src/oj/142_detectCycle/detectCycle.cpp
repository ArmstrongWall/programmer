//
// Created by johnny on 5/18/19.
//

#include "detectCycle.h"
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        ListNode* fast_ptr = head;
        ListNode* slow_ptr = head;
        ListNode* meet     = nullptr;

        while (fast_ptr) {
            slow_ptr = slow_ptr->next;
            if(fast_ptr->next) {
                fast_ptr = fast_ptr->next->next;
            } else {
                return nullptr;
            }

            if(fast_ptr == slow_ptr) {
                meet = fast_ptr;
                break;
            }

        }

        if(!meet) {
            return nullptr;
        }

        while (head != meet) {
            head = head->next;
            meet = meet->next;
        }
        return meet;
    }
};

int detectCycle(){
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    ListNode f(6);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &b;

    Solution solve;
    ListNode *node = solve.detectCycle(&a);
    if (node){
        printf("%d\n", node->val);
    }
    else{
        printf("NULL\n");
    }
    return 0;
}
