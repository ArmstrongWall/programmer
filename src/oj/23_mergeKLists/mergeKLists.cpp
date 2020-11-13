//
// Created by johnny on 5/19/19.
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
