//
// Created by johnny on 7/13/19.
//
#include <vector>
#include <queue>
#include <cstdio>
#include "binary_tree_right_side_view.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {

        std::vector<int> view;
        std::queue<std::pair<TreeNode *, int>> Q;
        if(root) {
            Q.push(std::make_pair(root,0));
        }
        while(!Q.empty()) {
            TreeNode *node = Q.front().first;
            int depth      = Q.front().second;
            Q.pop();

            if(view.size() == depth) {
                view.push_back(node->val);
            } else {
                view[depth] = node->val;
            }


            if (node->left) {
                Q.push(std::make_pair(node->left,depth + 1));
            }
            if (node->right) {
                Q.push(std::make_pair(node->right,depth + 1));
            }
        }
        return view;
    }
};