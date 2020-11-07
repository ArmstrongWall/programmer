//
// Created by johnny on 7/28/19.
//
#include <string>
#include "serialize_deserialize_BST.h"


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