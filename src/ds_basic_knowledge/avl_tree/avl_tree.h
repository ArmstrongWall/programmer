//
// Created by wzq on 2020/12/18.
//

#ifndef LEETCODE_AVL_TREE_H
#define LEETCODE_AVL_TREE_H
#include <iostream>
#include <exception>
using namespace std;

template<typename T>
class AvlTree {
public:
    AvlTree() : root(nullptr) {}
    AvlTree(const AvlTree<T> & rhs)  = default;
    AvlTree(AvlTree<T> &&rhs) : root(rhs.root) {
        rhs.root = nullptr;
    }
    ~AvlTree() {
        makeEmpty();
    }

    AvlTree &operator= (const AvlTree<T> & rhs) = default;
    AvlTree &operator= (AvlTree<T> && rhs)  noexcept = default;

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const T & val) {
        insert(val,root);
    }


private:
    struct AvlNode {
        T value;
        AvlNode * left;
        AvlNode * right;
        int height;
        AvlNode(const T & val, AvlNode *lt, AvlNode *rt, int h = 0)
        :value(val), left(lt), right(rt), height(h) {}
        AvlNode(T && val, AvlNode *lt, AvlNode *rt, int h = 0)
        :value(std::move(val)), left(lt), right(rt), height(h) {}
    };

    AvlNode* root;

    static const int MAX_HEIGHTSUB = 1;

    void insert(const T & val, AvlNode* root) {

        if(val > root->value) {
            insert(val,root->right);
        }

    }






};


#endif //LEETCODE_AVL_TREE_H
