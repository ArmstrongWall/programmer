//
// Created by Johnny on 2020/11/7.
//

#include <vector>
#include <iostream>
#include "buildTree.h"



struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right; 
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class Solution {
public:

    std::vector<int> copy(std::vector<int>& ori, int begin, int end) {
        std::vector<int> result;
        if(begin > end) {
            return result;
        }

        for(int i = begin; i <= end; i++) {
            result.push_back(ori[i]);

        }

        return result;
    }

    void print(std::vector<int>& ori) {
        for(int i = 0; i < ori.size(); i++) {
            std::cout << ori[i] << ",";
        }
        std::cout << "\n";
    }


    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {

        if(preorder.empty() || inorder.empty()
           || preorder.size() != inorder.size()) {
            return nullptr;
        }

        TreeNode* head = new TreeNode(preorder[0]);

        for(int i = 0; i < inorder.size(); i++) {
            if(inorder[i] == preorder[0]) {
                std::vector<int> left_child_preorder,left_child_inorder,
                        right_child_preorder,right_child_inorder;

                if(i > 0) {
                    left_child_preorder = copy(preorder, 1, i);
                    left_child_inorder  = copy(inorder,  0, i - 1);
                }
                if(i < inorder.size() - 1) {
                    right_child_preorder = copy(preorder, i+1, inorder.size() - 1);
                    right_child_inorder  = copy(inorder,  i+1, inorder.size() - 1);
                }

                head->left  = buildTree(left_child_preorder,left_child_inorder);
                head->right = buildTree(right_child_preorder,right_child_inorder);

            }
        }
        return head;
    }

    TreeNode* buildTree2(std::vector<int>& preorder, std::vector<int>& inorder) {
        if(preorder.empty()) {
            return nullptr;
        }
        TreeNode* head = new TreeNode(preorder[0]);
        for(int i = 0; i < inorder.size(); i++) {
            if(inorder[i] == preorder[0]) {
                std::vector<int> left_child_preorder(preorder.begin() + 1, preorder.begin() + 1 + i),
                        left_child_inorder(inorder.begin(),inorder.begin() + i),
                        right_child_preorder(preorder.begin() + i + 1, preorder.begin() + i + 1 + inorder.size() - 1 - i),
                        right_child_inorder(inorder.begin() + i + 1, inorder.begin() + i + 1 + inorder.size() - 1 - i);
                head->left  = buildTree(left_child_preorder,left_child_inorder);
                head->right = buildTree(right_child_preorder,right_child_inorder);
            }
        }
        return head;
    }
};