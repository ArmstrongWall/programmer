//
// Created by johnny on 6/30/19.
//

/* 113. 路径总和 II
 *
 * 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

5
/ \
            4   8
/   / \
          11  13  4
/  \    / \
        7    2  5   1

返回:

[
[5,4,11,2],
[5,8,4,5]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


#include <vector>
#include "path_sum_II.h"
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
    std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) {
        if(!root) {
            return {};
        }

        std::vector<std::vector<int>> result;
        std::vector<int> path;
        int path_value = 0;

        get_value(sum,path_value,root,path,result);

        return result;

    }

    void get_value( int sum,
                    int path_value,
                    TreeNode* node,
                    std::vector<int> &path,
                    std::vector<std::vector<int>> &result) {

        if(!node) {
            return;
        }

        path.push_back(node->val);
        path_value += node->val;

        get_value(sum,path_value,node->left,path,result);
        get_value(sum,path_value,node->right,path,result);


        if(!node->left && !node->right) {
            if(path_value == sum) {
                result.push_back(path);
            }
        }
        path.pop_back();
    }
};