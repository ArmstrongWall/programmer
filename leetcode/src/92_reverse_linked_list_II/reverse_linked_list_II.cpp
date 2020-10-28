//
// Created by johnny on 5/12/19.
//

#include "reverse_linked_list_II.h"
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {

        if(m == n) {
            return head;
        }

        ListNode* origin_head  = head;
        ListNode* pre_head     = nullptr;
        int reverse_num = n-m+1;

        while(head && --m) {
            pre_head = head;
            head     = head->next;
        }

        ListNode* segment_head  = head;
        ListNode* new_head      = nullptr;


        while(head && reverse_num) {
            ListNode* next = head->next;//保存当前节点的下一个节点
            head->next     = new_head;  //断掉当前节点，让它指向new_head，起反转作用
            new_head       = head;      //new_head是一个反转过的头指针，指向当前节点
            head           = next;      //往下一个节点移动
            reverse_num--;
        }

        segment_head->next = head;

        if(pre_head) {
            pre_head->next     = new_head;
            return origin_head;
        } else {
            return new_head;
        }
    }
};
class Solution1 {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {

        int i = 1;
        ListNode* ori_head       = head;
        ListNode* part_head_last = head;
        ListNode* part_head      = head;
        ListNode* travel         = nullptr;
        while(head) {
            if(i < m) {
                part_head_last = head;
                head           = head->next;
            }
            if(i >= m && i <= n) {
                if(i == m) {
                    part_head = head;
                    travel    = part_head_last;
                }
                ListNode* next = head->next;
                head->next     = travel;
                travel         = head;
                head           = next;
                if(i == n) {
                    part_head->next      = head;
                    part_head_last->next = travel;
                    break;
                }
            }
            i++;
        }
        return ori_head;
    }
};

void reverse_between() {
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);

    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    std::cout << "before reverse_between" << std::endl;
    ListNode* head = &a;
    while(head) {
        std::cout << head->val << std::endl;
        head = head->next;
    }

    Solution s;
    ListNode* reverse_head = s.reverseBetween(&a,2,4);

    std::cout << "after reverse_between" << std::endl;

    while(reverse_head) {
        std::cout << reverse_head->val << std::endl;
        reverse_head = reverse_head->next;
    }
}