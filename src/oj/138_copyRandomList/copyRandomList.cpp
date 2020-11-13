//
// Created by johnny on 5/19/19.
//

//138. 复制带随机指针的链表
//https://leetcode-cn.com/problems/copy-list-with-random-pointer/
//        给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
//
//要求返回这个链表的 深拷贝。
//
//我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
//
//val：一个表示 Node.val 的整数。
//random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
//
//
//
//示例 1：
//
//输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
//输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
//
//示例 2：
//
//输入：head = [[1,1],[2,1]]
//输出：[[1,1],[2,1]]
//
//示例 3：
//
//输入：head = [[3,null],[3,0],[3,null]]
//输出：[[3,null],[3,0],[3,null]]
//
//示例 4：
//
//输入：head = []
//输出：[]
//解释：给定的链表为空（空指针），因此返回 null。
//
//
//
//提示：
//
//-10000 <= Node.val <= 10000
//Node.random 为空（null）或指向链表中的节点。
//节点数目不超过 1000 。
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
