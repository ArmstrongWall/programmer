#include <iostream>
#include "include.h"

void BinaryHeapDemo();

int main() {
    std::cout << "Hello, World!" << std::endl;

    BinaryHeapDemo();

    return 0;
}

void BinaryHeapDemo() {
    auto heap = new BinaryHeap<int>;
    std::cout << "before insert" << std::endl;
    heap->printBinaryHeap();

    heap->insert(14);
    std::cout << "after insert" << std::endl;
    heap->printBinaryHeap();
}