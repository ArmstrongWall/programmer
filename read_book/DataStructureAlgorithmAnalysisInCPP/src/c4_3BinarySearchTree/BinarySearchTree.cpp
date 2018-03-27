//
// Created by johnny on 1/10/18.
//
#include "BinarySearchTree.h"

template <typename T>
binarySearchTree<T>::binarySearchTree() {

}

template <typename T>
bool binarySearchTree<T>::contains(const T &x) const {
    return contains(x,root);
}

template <typename T>
void binarySearchTree<T>::insert(const T &x) {
    insert(x,root);
}

template <typename T>
void binarySearchTree<T>::insert(T &&x) {

}

template <typename T>
const T& binarySearchTree<T>::findMax() const {
    return findMax(root);
}

template <typename T>
void binarySearchTree<T>::remove(const T &x) {
    remove(x,root);
}

template <typename T>
bool binarySearchTree<T>::contains(const T &x, binaryNode<T> *tree) const {
    if(tree == nullptr)
        return false;
    if(x < tree->element)
        contains(x,tree->left);//small is left node
    else if(x > tree->element)
        contains(x,tree->right);
    else
        return true;//get node
}

template <typename T>
binaryNode<T> * binarySearchTree<T>::findMax(binaryNode<T> *tree) const {

}
