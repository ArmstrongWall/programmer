//
// Created by johnny on 5/19/19.
//

#include "copyRandomList.h"

#include <iostream>
#include <map>
#include <vector>


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }

};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) {
            return nullptr;
        }

        Node*               ori_head = head;
        std::map<Node*,int> node_id;
        std::vector<Node*>  node_vec;
        int id = 0;
        while(head) {
            node_id[head] = id;
            node_vec.push_back(new Node(head->val,nullptr,nullptr));
            id++;
            head = head->next;
        }


        for(int i = 0; i < node_vec.size(); i++) {
            if(ori_head->random) {
                id = node_id[ori_head->random];
                node_vec[i]->random = node_vec[id];
            }
            ori_head = ori_head->next;
            if(i) {
                node_vec[i-1]->next = node_vec[i];
            }
        }



        return node_vec[0];

    }
};

int copyRandomList(){
    Node a(1,nullptr,nullptr);
    Node b(2,nullptr,nullptr);
    Node c(3,nullptr,nullptr);
    Node d(4,nullptr,nullptr);
    Node e(5,nullptr,nullptr);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    a.random = &c;
    b.random = &d;
    c.random = &c;
    e.random = &d;
    Solution solve;
    Node *head = solve.copyRandomList(&a);
    while(head){
        printf("label = %d ", head->val);
        if (head->random){
            printf("rand = %d\n", head->random->val);
        }
        else{
            printf("rand = NULL\n");
        }
        head = head->next;
    }
    return 0;
}
