//
// Created by Johnny on 2020/11/1.
//

#include <algorithm>
#include "maxDepth.h"
/**
 * Definition for a binary tree node. */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    int maxDepth(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }

        if(root->left == nullptr && root->right == nullptr) {
            return 1;
        }
        int left_depth  = maxDepth(root->left);
        int right_depth = maxDepth(root->right);

        return std::max(1 + left_depth, 1 + right_depth);
    }
};