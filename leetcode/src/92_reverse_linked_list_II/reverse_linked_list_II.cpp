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

class SolutionByMei{
public:
       ListNode* reverseBetween(ListNode* head, int m, int n){
             int i = 1;
             ListNode* pNode_m_1 = nullptr;
             ListNode* new_head = nullptr;
             ListNode* result= head;
             while(i <= n) {
	    					if(i == m-1) pNode_m_1 = head;
                if(i >= m){
                       ListNode* pnext = head->next;
                       head->next      = new_head;
                       new_head        = head;
                       head            = pnext;
                }
                else   head = head->next;
                i++;
           	 }
             if(m == 1) {
	    					result->next = head;//m和n+1
                result= new_head;
             }
             else {
             	   pNode_m_1->next->next = head;//m和n+1
             	   pNode_m_1->next = new_head;//m-1和n
             }
             return result;
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
    ListNode* reverse_head = s.reverseBetween(&a,3,4);

    std::cout << "after reverse_between" << std::endl;

    while(reverse_head) {
        std::cout << reverse_head->val << std::endl;
        reverse_head = reverse_head->next;
    }
}
