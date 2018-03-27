//
// Created by johnny on 1/10/18.
//
#include <iostream>
using namespace std;

#ifndef DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYSEARCHTREE_H
#define DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYSEARCHTREE_H

template <typename T>
//define a binarySearchTree node
struct binaryNode{
    T element;
    binaryNode<T> * left;
    binaryNode<T> * right;
    binaryNode( const T & theElement, binaryNode * lt, binaryNode * rt):
            element{theElement},left{lt},right{rt}{};

    binaryNode( T && theElement, binaryNode * lt, binaryNode * rt):
            element{move(theElement)},left{lt},right{rt}{};
};

template <typename T>
class binarySearchTree{
    //binarySearchTree operation
public:
    binarySearchTree();
    binarySearchTree(const binarySearchTree & rhs);//right value
    binarySearchTree(binarySearchTree && lhs);     //left value
    ~binarySearchTree();
    
    const T & findMin() const ;//find Min operation in Tree
    const T & findMax() const ;//find Max operation in Tree
    bool contains(const T & x) const ;//operation whether x is contained in Tree
    bool isEmpty() const ;//operation whether Tree is empty
    void printTree(ostream & out = cout) const ;

    void makeEmpty() const;//let tree  empty
    void insert(const T & x);//insert operation Tree
    void insert(T && x);//
    void remove(const T & x);//remove operation from Tree

    //copy tree in right and left value
    binarySearchTree &operator=(const binarySearchTree& rhs);
    binarySearchTree &operator=(binarySearchTree&& lhs);


private:


    //root node
    binaryNode<T> * root;

    //insert a node into Tree(right and left value)
    void insert(const T & x , binaryNode<T> * tree);
    void insert(T && x , binaryNode<T> * tree);

    //remove a node from Tree
    void remove(const T & x , binaryNode<T> * tree);

    //find Min and Maxvalue in Tree
    binaryNode<T> * findMin(binaryNode<T> * tree) const ;
    binaryNode<T> * findMax(binaryNode<T> * tree) const ;

    //whether x is contained in Tree
    bool contains(const T & x , binaryNode<T> * tree) const ;

    //let tree  empty
    void makeEmpty(binaryNode<T> * tree);

    //print tree
    void printTree(binaryNode<T> * tree, ostream & out) const;

    //clone a tree
    binaryNode<T> * clone(binaryNode<T> * tree) const;
};



#endif //DATASTRUCTUREALGORITHMANALYSISINCPP_BINARYSEARCHTREE_H
