//
// Created by johnny on 7/6/19.
//
#include <vector>
#include <cstdio>

#include "lowest_commonance_ancestor.h"
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        std::vector<TreeNode*>  path_p,   path_q;
        std::vector<TreeNode*>  result_p, result_q;

        int finish = 0;
        preorder(root,p,path_p,result_p,finish);

        finish = 0;
        preorder(root,q,path_q,result_q,finish);

        int path_len = 0;
        if (result_p.size() < result_q.size()){
            path_len = result_p.size();
        }
        else{
            path_len = result_q.size();
        }
        TreeNode *result = nullptr;
        for (int i = 0; i < path_len; i++){
            if (result_p[i] == result_q[i]){
                result = result_p[i];
            }
        }
        return result;
    }

    void preorder(  TreeNode* node,
                    TreeNode* target,
                    std::vector<TreeNode*> &path,
                    std::vector<TreeNode*> &result,
                    int finish) {
        if(!node || finish) {
            return;
        }
        path.push_back(node);
        if(node == target) {
            finish = 1;
            result = path;
        }

        preorder(node->left,target,path,result,finish);
        preorder(node->right,target,path,result,finish);
        path.pop_back();
    }

};

int lowestCommonAncestor(){
    TreeNode a(3);
    TreeNode b(5);
    TreeNode c(1);
    TreeNode d(6);
    TreeNode e(2);
    TreeNode f(0);
    TreeNode x(8);
    TreeNode y(7);
    TreeNode z(4);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &x;
    e.left = &y;
    e.right = &z;

    Solution solve;
    TreeNode *result = solve.lowestCommonAncestor(&a, &b, &f);
    printf("lowestCommonAncestor = %d\n", result->val);
    result = solve.lowestCommonAncestor(&a, &d, &z);
    printf("lowestCommonAncestor = %d\n", result->val);
    result = solve.lowestCommonAncestor(&a, &b, &y);
    printf("lowestCommonAncestor = %d\n", result->val);

    return 0;
}