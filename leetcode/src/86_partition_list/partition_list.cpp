//
// Created by johnny on 5/19/19.
//

#include "partition_list.h"

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {

        ListNode less_head(0);
        ListNode* less_walk = &less_head;
        ListNode more_head(0);
        ListNode* more_walk = &more_head;

        while (head) {
            if(head->val >= x) {
                more_walk->next = head;
                more_walk       = head;
            } else {
                less_walk->next = head;
                less_walk       = head;
            }
            head = head->next;
        }

        less_walk->next = more_head.next;
        more_walk->next = nullptr;

        return less_head.next;
    }
};

int partition(){
    ListNode a(1);
    ListNode b(4);
    ListNode c(3);
    ListNode d(2);
    ListNode e(5);
    ListNode f(2);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    Solution solve;
    ListNode *head = solve.partition(&a, 3);
    while(head){
        printf("%d\n", head->val);
        head = head->next;
    }
    return 0;
}
