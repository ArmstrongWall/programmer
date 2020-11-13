//
// Created by johnny on 5/19/19.
//

//23. 合并K个升序链表
//https://leetcode-cn.com/problems/merge-k-sorted-lists/
//        给你一个链表数组，每个链表都已经按升序排列。
//
//请你将所有链表合并到一个升序链表中，返回合并后的链表。
//
//
//
//示例 1：
//
//输入：lists = [[1,4,5],[1,3,4],[2,6]]
//输出：[1,1,2,3,4,4,5,6]
//解释：链表数组如下：
//[
//1->4->5,
//1->3->4,
//2->6
//]
//将它们合并到一个有序链表中得到。
//1->1->2->3->4->4->5->6
//
//示例 2：
//
//输入：lists = []
//输出：[]
//
//示例 3：
//
//输入：lists = [[]]
//        输出：[]
//
//
//
//提示：
//
//k == lists.length
//0 <= k <= 10^4
//0 <= lists[i].length <= 500
//-10^4 <= lists[i][j] <= 10^4
//lists[i] 按 升序 排列
//        lists[i].length 的总和不超过 10^4
//


#include "mergeKLists.h"
#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};


class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {

        if(lists.empty()) {
            return nullptr;
        } else if(lists.size() == 1) {
            return lists[0];
        }

        std::vector<ListNode*> front_list;
        std::vector<ListNode*> back_list;

        int mid = lists.size()/2;

        for(int i = 0; i < mid; i++) {
            front_list.push_back(lists[i]);
        }

        for(int i = mid; i < lists.size(); i++) {
            back_list.push_back(lists[i]);
        }

        ListNode* l1 = nullptr;
        ListNode* l2 = nullptr;

        if(!front_list.empty()) {
            l1 = mergeKLists(front_list);
        }
        if(!back_list.empty()) {
            l2 = mergeKLists(back_list);
        }

        return mergeTwoLists(l1,l2);

    }

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

int mergeKLists(){
    ListNode a(1);
    ListNode b(4);
    ListNode c(6);
    ListNode d(0);
    ListNode e(5);
    ListNode f(7);
    ListNode g(1);
    ListNode h(3);
    a.next = &b;
    b.next = &c;
    d.next = &e;
    e.next = &f;
    g.next = &h;
    Solution solve;
    std::vector<ListNode *> lists;
    lists.push_back(&a);
    lists.push_back(&d);
    lists.push_back(&g);
    ListNode *head = solve.mergeKLists(lists);
    while(head){
        printf("%d\n", head->val);
        head = head->next;
    }
    return 0;
}
