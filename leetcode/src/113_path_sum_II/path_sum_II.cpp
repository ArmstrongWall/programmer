//
// Created by johnny on 6/30/19.
//

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