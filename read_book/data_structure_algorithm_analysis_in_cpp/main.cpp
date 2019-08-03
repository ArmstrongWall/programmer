#include <iostream>
#include "include.h"
void BinaryHeapDemo();
void binarySearchTreeDemo();
void sortDemo();

int main() {
    std::cout << "Hello, D&A World!" << std::endl;

//    BinaryHeapDemo();
    binarySearchTreeDemo();
//    sortDemo();

    return 0;
}

void BinaryHeapDemo() {
    std::cout << "Binary Heap Demo" << std::endl;
    auto heap = new BinaryHeap<int>;
    std::cout << "before insert" << std::endl;
    heap->printBinaryHeap();

    heap->insert(14);
    std::cout << "after insert" << std::endl;
    heap->printBinaryHeap();
}

void binarySearchTreeDemo() {
    std::cout << "binary Search Tree Demo" << std::endl;
    //define a tree
    auto tree1 = new binarySearchTree<int>;
    std::cout << "tree1" << std::endl;
    tree1->printTree();

    //get tree height
    std::cout << "tree1 height is" <<tree1->height()<< std::endl;

    //clone a tree
    auto tree2 = new binarySearchTree<int>{*tree1};
    std::cout << std::endl << "tree2" << std::endl;
    tree2->printTree();

    std::cout << "tree2->contains" << tree2->contains(23);

}

void sortDemo() {
    std::cout << "insertion Sort Demo" << std::endl;

    auto sorter = new sort<int>;
    vector<int> a {34,8,64,51,32,21};

//    sorter->insertionSort(a);
//    sorter->print(a);

    sorter->mergeSort(a);
    sorter->print(a);

}


