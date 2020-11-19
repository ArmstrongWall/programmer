//
// Created by wzq on 2020/11/20.
//

/*
 * https://leetcode-cn.com/problems/symmetric-tree/
101. 对称二叉树

        给定一个二叉树，检查它是否是镜像对称的。



例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

1
/ \
  2   2
/ \ / \
3  4 4  3



但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

1
/ \
  2   2
\   \
   3    3



进阶：

你可以运用递归和迭代两种方法解决这个问题吗？
*/


#include "isSymmetric.h"


class Solution {
public:

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    int tree_h(TreeNode* root) {
        if(root) {
            int l = 0, r = 0;
            if(root->left)  l = tree_h(root->left);
            if(root->right) r = tree_h(root->right);
            return l >= r ? l + 1 : r + 1;
        }
        return 0;
    }

    bool isSymmetric(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr && root2 == nullptr) {
            return true;
        }

        if(root1 == nullptr || root2 == nullptr) {
            return false;
        }

        if(root1->val != root2->val) {
            return false;
        }

        return isSymmetric(root1->left,root2->right) && isSymmetric(root1->right, root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root,root);
    }

};