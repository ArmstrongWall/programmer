//
// Created by johnny on 1/10/18.
//
#include "BinarySearchTree.h"

template <typename T>
binarySearchTree<T>::binarySearchTree():root{nullptr} {
    vector<int> node {10,23,40,50,60,59,32,66};
    for(auto x:node) {
        insert(x);
    }
}

template <typename T>
binarySearchTree<T>::binarySearchTree(const binarySearchTree &rhs):root{nullptr} {
    root = clone(rhs.root);
}

template <typename T>
binarySearchTree<T>::~binarySearchTree() {
    makeEmpty();
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
    insert(std::move(x),root);
}

template <typename T>
const T& binarySearchTree<T>::findMax() const {
    return findMax(root);
}

template <typename T>
const T& binarySearchTree<T>::findMin() const {
    return findMin(root);
}

template <typename T>
void binarySearchTree<T>::remove(const T &x) {
    remove(x,root);
}
template <typename T>
bool binarySearchTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void binarySearchTree<T>::makeEmpty() {
    makeEmpty(root);
}

template <typename T>
bool binarySearchTree<T>::contains(const T &x, binaryNode<T> *tree) const {
    if(tree == nullptr)//empty tree
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
    if(tree == nullptr)//empty tree
        return nullptr;

    if(tree->right != nullptr)
        return findMax(tree->right);
    else if (tree->right == nullptr)
        return tree;
}

template <typename T>
binaryNode<T> * binarySearchTree<T>::findMin(binaryNode<T> *tree) const {
    if(tree == nullptr)//empty tree
        return nullptr;

    //no recursion
    while(tree->left) {
        tree = tree->left;
    }

    return tree;
}

template <typename T>
void binarySearchTree<T>::insert(const T &x, binaryNode<T> * &tree) {
    if(!tree) {// no exist node
        tree = new binaryNode<T>{x, nullptr, nullptr};
    }
    else if(x < tree->element)
        insert(x,tree->left);//small is left node
    else if(x > tree->element)
        insert(x,tree->right);//big is right node
    else
        ;//x = node , do nonething
}

template <typename T>
void binarySearchTree<T>::insert(T &&x, binaryNode<T> * &tree) {
    if(!tree) {// no exist node,
        tree = new binaryNode<T>{std::move(x), nullptr, nullptr};
    }
    else if(x < tree->element)
        insert(std::move(x),tree->left);//small is left node
    else if(x > tree->element)
        insert(std::move(x),tree->right);//big is right node
    else
        ;//x = node , do nothing
}

template <typename T>
void binarySearchTree<T>::remove(const T &x, binaryNode<T> * &tree) {
    if(tree == nullptr) {
        return;
    }
    //find the node need to remove
    if(x < tree->element ){
        remove(x,tree->left);
    }
    else if(x > tree->element) {
        remove(x,tree->right);
    }
        //has find the node
    else if( tree->right != nullptr && tree->left != nullptr) {//has left and right child
        //find right child family min node  and use it to replace current node
        tree->element = findMin(tree->right)->element;
        //remove the min node in right child family
        remove(tree->element,tree->right);
    }
    else if( tree->right == nullptr && tree->left == nullptr) {//has no child
        delete tree;
    }
    else {//has only one child
        binaryNode<T>* tempNode = tree;//node
        tree = (tree->left == nullptr) ?tree->right:tree->left;
        //replace node 和链表的删除不一样，链表是对后继指针的操作，此处是对整个节点指针的操作
        delete tempNode;//delete old node
    }
}

template <typename T>
void binarySearchTree<T>::makeEmpty(binaryNode<T> * tree) {
    if(tree != nullptr) {
        makeEmpty(tree->left);
        makeEmpty(tree->right);
        delete tree;
    }
    tree = nullptr;
}

template <typename T>
binaryNode<T>* binarySearchTree<T>::clone(binaryNode<T> *tree) const {
    if(tree != nullptr) {
        clone(tree->left);
        clone(tree->right);
        return  new binaryNode<T>{tree->element, tree->left, tree->right};
    }
    return nullptr;
}


template <typename T>
void binarySearchTree<T>::printTree(ostream &out) const {
    if(isEmpty())
        out << "Empty tree" << endl;
    else
        printTree(root,out);
}

template <typename T>
void binarySearchTree<T>::printTree(binaryNode<T> * tree, ostream & out) const {
    if(tree != nullptr) {
        out << tree->element ;
        if(tree->left != nullptr || tree->right != nullptr) {
            out << endl;
        }
        if(tree->left != nullptr) {
            out << " /";
        }
        if(tree->right != nullptr) {
            out << " \\"<<endl ;
        }
        printTree(tree->left,out);
        out << " ";
        printTree(tree->right,out);
    }
    else
        return;
}

template <typename T>
void binarySearchTree<T>::preOrderTravelTree(binaryNode<T> * tree, ostream & out) const {
    if(tree != nullptr) {
        out << tree->element << endl;//father is before child
        printTree(tree->left,out);
        printTree(tree->right,out);
    }
    else
        return;
}

template <typename T>
void binarySearchTree<T>::inOrderTravelTree(binaryNode<T> * tree, ostream & out) const {
    if(tree != nullptr) {
        printTree(tree->left,out);
        out << tree->element << endl;//father is between two child
        printTree(tree->right,out);
    }
    else
        return;
}

template <typename T>
void binarySearchTree<T>::postOrderTravelTree(binaryNode<T> * tree, ostream & out) const {
    if(tree != nullptr) {
        printTree(tree->left,out);
        printTree(tree->right,out);
        out << tree->element << endl;//father is after two child
    }
    else
        return;
}

template <typename T>
int binarySearchTree<T>::height() const {
    return height(root);
}

template <typename T>
int binarySearchTree<T>::height(binaryNode<T> *tree) const {
    if(tree == nullptr) {
        return 0 ;
    }

    if(tree->right != nullptr || tree->left != nullptr ) {
        return 1+max(height(tree->right),height(tree->left));
    }
}
