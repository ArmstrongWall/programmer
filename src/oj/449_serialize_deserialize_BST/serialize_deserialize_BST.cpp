//
// Created by johnny on 7/28/19.
//
#include <string>
#include "serialize_deserialize_BST.h"

/* 449
 * 序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑。



示例 1：

输入：root = [2,1,3]
输出：[2,1,3]

示例 2：

输入：root = []
输出：[]



提示：

树中节点数范围是 [0, 104]
0 <= Node.val <= 104
题目数据 保证 输入的树是一棵二叉搜索树。



注意：不要使用类成员/全局/静态变量来存储状态。 你的序列化和反序列化算法应该是无状态的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/serialize-and-deserialize-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {

        std::string str_val;
        preOrderTravelTree(root,str_val);
        return str_val;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        TreeNode * root = nullptr;

        std::string val_s;
        for(auto &x : data) {
            int val_i;
            if(x == '#') {
                val_i = std::stoi(val_s);
                val_s.clear();
                insert(val_i,root);
            } else {
                val_s += x;
            }
        }
        return root;

    }

    void preOrderTravelTree(TreeNode * tree, std::string& str_val) {
        if(tree != nullptr) {
            str_val += std::to_string(tree->val) + '#';
            preOrderTravelTree(tree->left,str_val);
            preOrderTravelTree(tree->right,str_val);
        }
        else
            return;
    }

    void insert(const int &x, TreeNode * &tree) {
        if(!tree) {// no exist node
            tree = new TreeNode{x};
        }
        else if(x < tree->val)
            insert(x,tree->left);//small is left node
        else if(x > tree->val)
            insert(x,tree->right);//big is right node

    }


};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));