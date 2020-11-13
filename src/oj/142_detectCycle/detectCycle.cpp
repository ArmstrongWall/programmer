//
// Created by johnny on 5/18/19.
//

//142. 环形链表 II
//https://leetcode-cn.com/problems/linked-list-cycle-ii/
//给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
//
//为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。
//
//说明：不允许修改给定的链表。
//
//进阶：
//
//你是否可以使用 O(1) 空间解决此题？
//
//
//
//示例 1：
//
//输入：head = [3,2,0,-4], pos = 1
//输出：返回索引为 1 的链表节点
//        解释：链表中有一个环，其尾部连接到第二个节点。
//
//示例 2：
//
//输入：head = [1,2], pos = 0
//输出：返回索引为 0 的链表节点
//        解释：链表中有一个环，其尾部连接到第一个节点。
//
//示例 3：
//
//输入：head = [1], pos = -1
//输出：返回 null
//解释：链表中没有环。
//
//
//
//提示：
//
//链表中节点的数目范围在范围 [0, 104] 内
//-105 <= Node.val <= 105
//pos 的值为 -1 或者链表中的一个有效索引
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
