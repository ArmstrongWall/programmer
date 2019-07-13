//
// Created by johnny on 7/13/19.
//
#include <vector>
#include <queue>
#include <cstdio>
#include "binary_tree_breadth_first_search.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void BFS_print(TreeNode* root){
    std::queue<TreeNode *> Q;
    Q.push(root);
    while(!Q.empty()){
        TreeNode *node = Q.front();
        Q.pop();
        printf("[%d]\n", node->val);
        if (node->left){
            Q.push(node->left);
        }
        if (node->right){
            Q.push(node->right);
        }
    }
}

int BFS() {
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
    BFS_print(&a);
    return 0;
}
