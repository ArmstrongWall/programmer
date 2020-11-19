//
// Created by wzq on 2020/11/19.
//
/*
 * https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/
剑指 Offer 26. 树的子结构

        输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

3
/ \
   4   5
/ \
 1   2
给定的树 B：

4
/
1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：

输入：A = [1,2,3], B = [3,1]
输出：false

示例 2：

输入：A = [3,4,5,1,2], B = [4,1]
输出：true

限制：

0 <= 节点个数 <= 10000

*/

#include <cstdio>
#include "isSubStructure.h"
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
public:

    bool has_same_sub(TreeNode* A, TreeNode* B) {
        if(B == NULL) {
            return true;
        }
        if(A == NULL) {
            return false;
        }

        if(A != nullptr && B != NULL) {
            if(A->val == B->val) {
                if(has_same_sub(A->left, B->left) && has_same_sub(A->right, B->right)) {
                    return true;
                }
            } else {
                return false;
            }
        }
        return false;
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {

        if(A != NULL && B != NULL) {
            if(has_same_sub(A,B)) {
                return true;
            }
            if(isSubStructure(A->left,B)) {
                return true;
            }
            if(isSubStructure(A->right,B)) {
                return true;
            }
        }
        return false;

    }
};