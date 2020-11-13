//
// Created by johnny on 5/19/19.
//

//21. 合并两个有序链表
//https://leetcode-cn.com/problems/merge-two-sorted-lists/
//        将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
//
//
//
//示例：
//
//输入：1->2->4, 1->3->4
//输出：1->1->2->3->4->4
//


#include "mergeTwoLists.h"
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

        ListNode  merge_head(0);
        ListNode* merge_walk = &merge_head;

        while (l1 && l2) {
            if(l1->val <= l2->val) {
                merge_walk->next = l1;
                merge_walk       = l1;
                l1               = l1->next;
            } else {
                merge_walk->next = l2;
                merge_walk       = l2;
                l2               = l2->next;
            }
        }

        if(l1) {
            merge_walk->next = l1;
        }

        if(l2) {
            merge_walk->next = l2;
        }

        if(!merge_head.next) {
            return nullptr;
        } else {
            return merge_head.next;
        }
    }
};

int mergeTwoLists(){
    ListNode a(1);
    ListNode b(4);
    ListNode c(6);
    ListNode d(0);
    ListNode e(5);
    ListNode f(7);
    ListNode g(9);
    a.next = &b;
    b.next = &c;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    Solution solve;
    ListNode *head = solve.mergeTwoLists(&a, &d);
    while(head){
        printf("%d\n", head->val);
        head = head->next;
    }
    return 0;
}
