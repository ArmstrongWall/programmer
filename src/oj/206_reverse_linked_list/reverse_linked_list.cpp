//
// Created by wzq on 18-6-25.
//

/*
 *
 * 206. 反转链表
 * 反转一个单链表。
https://leetcode-cn.com/problems/reverse-linked-list/
示例:

输入: 1->2->3->4->5->NULL
        输出: 5->4->3->2->1->NULL
        */
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        while(head) {
            ListNode* next = head->next;//保存当前节点的下一个节点
            head->next     = new_head;  //断掉当前节点，让它指向new_head，起反转作用
            new_head       = head;      //new_head是一个反转过的头指针，指向当前节点
            head           = next;      //往下一个节点移动
        }
        return new_head;
    }
};

void reverseList() {
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);

    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = nullptr;

    ListNode* head = &a;
    while(head) {
        std::cout << head->val << std::endl;
        head = head->next;
    }

    Solution s;
    ListNode* reverse_head = s.reverseList(&a);

    std::cout << "after reverse" << std::endl;

    while(reverse_head) {
        std::cout << reverse_head->val << std::endl;
        reverse_head = reverse_head->next;
    }
}

