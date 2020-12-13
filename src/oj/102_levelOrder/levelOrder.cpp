//
// Created by wzq on 2020/12/13.
//

/*给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。



示例：
二叉树：[3,9,20,null,null,15,7],

3
/ \
  9  20
/  \
   15   7

返回其层次遍历结果：

[
[3],
[9,20],
[15,7]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <vector>
#include <queue>
#include "levelOrder.h"
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(!root) {
            return result;
        }
        vector<int> store;

        queue<TreeNode*> q_father,q_child;
        q_father.push(root);
        while(!q_father.empty()) {
            auto node = q_father.front();
            store.push_back(node->val);
            q_father.pop();
            if(node->left) {
                q_child.push(node->left);
            }
            if(node->right) {
                q_child.push(node->right);
            }
            if(q_father.empty()) {
                result.push_back(store);
                store.clear();
                q_father = q_child;
                while(!q_child.empty()) {
                    q_child.pop();
                }
            }
        }

        return result;
    }
};