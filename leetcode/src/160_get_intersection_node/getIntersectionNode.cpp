//
// Created by johnny on 5/18/19.
//

#include "getIntersectionNode.h"
#include <iostream>
#include <set>
#include <cmath>


struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};

class Solution {
public:
    int count_length(ListNode* head) {
        int count = 0;
        while (head) {
            head = head->next;
            count++;
        }
        return count;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

        int length_a = count_length(headA);
        int length_b = count_length(headB);

        int length_diff =  fabs(length_a - length_b);


        if(length_a >= length_b) {
            while (length_diff--) {
                headA = headA->next;
            }
        } else {
            while (length_diff--) {
                headB = headB->next;
            }
        }

        while (headA) {
            if(headA == headB) {
                return headA;
            }
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;

    }
};

int getIntersectionNode() {

    ListNode a1(1);
    ListNode a2(2);
    ListNode b1(3);
    ListNode b2(4);
    ListNode b3(5);
    ListNode c1(6);
    ListNode c2(7);
    ListNode c3(8);
    a1.next = &a2;
    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;
    b1.next = &b2;
    b2.next = &b3;
    b3.next = &c1;

    Solution solve;
    ListNode *result = solve.getIntersectionNode(&a1, &b1);
    printf("%d\n", result->val);
    return 0;
}