//
// Created by johnny on 7/13/19.
//

#include <vector>
#include <cstdio>

#include "flatten_binary_tree2linked_list.h"
/**
 * Definition for a binary tree node.
 * */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* last = nullptr;
        preorder(root,last);
    }

private:
    void preorder(TreeNode* &node, TreeNode* &last) {
        if(!node) {
            return;
        }
        if(!node->left && !node->right) {
            last = node;
            return;
        }

        TreeNode* left_last  = nullptr;
        TreeNode* left_copy  = node->left;
        TreeNode* right_copy = node->right;

        if(left_copy) {
            preorder(left_copy,last);
            node->left = nullptr;
            node->right = left_copy;
            if(last) {
                left_last = last;
            }
        }

        if(right_copy) {
            preorder(right_copy,last);
            if(left_last) {
                left_last->right = right_copy;
            }
        }

    }
};

int flatten(){
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(5);
    TreeNode d(3);
    TreeNode e(4);
    TreeNode f(6);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    Solution solve;
    solve.flatten(&a);
    TreeNode *head = &a;
    while(head){
        if (head->left){
            printf("ERROR\n");
        }
        printf("[%d]", head->val);
        head = head->right;
    }
    printf("\n");
    return 0;
}