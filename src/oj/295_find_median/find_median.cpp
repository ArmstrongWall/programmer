//
// Created by johnny on 6/12/19.
//

//
// 295. 数据流的中位数
// 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
//https://leetcode-cn.com/problems/find-median-from-data-stream/
//例如，
//
//[2,3,4] 的中位数是 3
//
//[2,3] 的中位数是 (2 + 3) / 2 = 2.5
//
//设计一个支持以下两种操作的数据结构：
//
//void addNum(int num) - 从数据流中添加一个整数到数据结构中。
//double findMedian() - 返回目前所有元素的中位数。
//
//示例：
//
//addNum(1)
//addNum(2)
//findMedian() -> 1.5
//addNum(3)
//findMedian() -> 2
//
//进阶:
//
//如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
//如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/find-median-from-data-stream
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

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
