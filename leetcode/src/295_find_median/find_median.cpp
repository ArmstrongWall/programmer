//
// Created by johnny on 6/12/19.
//

#include <queue>
#include <vector>
#include <iostream>


#include "find_median.h"

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    std::priority_queue<int,std::vector<int>,std::greater<>> min_heap;
    std::priority_queue<int,std::vector<int>,std::less<>>    max_heap;


    void addNum(int num) {

        if(min_heap.size() == max_heap.size()) {
            if(max_heap.empty()) {
                max_heap.push(num);
            }
            else if(num >= min_heap.top()) {
                min_heap.push(num);
            } else {
                max_heap.push(num);
            }
        } else if(min_heap.size() - max_heap.size() == 1) {
            if(num <= min_heap.top()) {
                max_heap.push(num);
            } else {
                max_heap.push(min_heap.top());
                min_heap.pop();
                min_heap.push(num);
            }
        } else if(max_heap.size() - min_heap.size() == 1) {
            if(num >= max_heap.top()) {
                min_heap.push(num);
            } else {
                min_heap.push(max_heap.top());
                max_heap.pop();
                max_heap.push(num);
            }
        } else {
            std::cout << "addnum error\n";
        }
    }

    double findMedian() {
        if(max_heap.size() == min_heap.size()) {
            return (static_cast<double>(max_heap.top()) + static_cast<double>(min_heap.top()))/2.0;
        } else if((max_heap.size() - min_heap.size()) == 1) {
            return static_cast<double>(max_heap.top());
        } else if((min_heap.size() - max_heap.size()) == 1) {
            return static_cast<double>(min_heap.top());
        } else {
            std::cout << "findMedian error\n";
            return 0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int findMedian() {
    MedianFinder m;
    int num[] = {6, 10, 1, 7, 99, 4, 33};
    for(int i = 0; i < 7; i++) {
        m.addNum(num[i]);
        std::cout << "\nfindMedian :" << m.findMedian();
    }
}
