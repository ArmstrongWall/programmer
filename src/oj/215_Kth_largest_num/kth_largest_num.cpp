/**
 *
 * @file   kth_largest_num.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-6-12
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-6-12    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

//215. 数组中的第K个最大元素
//https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
//        在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
//
//示例 1:
//
//输入: [3,2,1,5,6,4] 和 k = 2
//输出: 5
//
//示例 2:
//
//输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
//输出: 4
//
//说明:
//
//你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。

#include <iostream>
#include <vector>
#include <queue>
#include "kth_largest_num.h"


class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue<int,std::vector<int>,std::greater<int>> pri_queue;
        for(auto x:nums) {
            if(pri_queue.size() < k) {
                pri_queue.push(x);

            } else if(x > pri_queue.top()) {
                pri_queue.pop();
                pri_queue.push(x);

            }
        }
        if(!pri_queue.empty()) {
            return pri_queue.top();
        } else {
            return 0;
        }
    }
};

int findKthLargest() {
    std::vector<int> num;
    num.push_back(3);
    num.push_back(2);
    num.push_back(1);
    num.push_back(6);
    num.push_back(5);
    num.push_back(4);

    Solution solve;
    std::cout << "result is " << solve.findKthLargest(num,2) ;

}