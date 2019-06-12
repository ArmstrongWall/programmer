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