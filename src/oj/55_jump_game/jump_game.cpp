//
// Created by johnny on 6/23/19.
//

/*
45. 跳跃游戏 II

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

说明:

假设你总是可以到达数组的最后一个位置。
 https://leetcode-cn.com/problems/jump-game-ii/
*/


#include <vector>
#include <stack>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include "jump_game.h"

class Solution {
public:
    bool canJump(std::vector<int>& nums) {

        if(nums.size() == 1) {
            return true;
        } else if(nums.empty()) {
            return false;
        }

        int i = 0;
        while(i < nums.size()) {

            if(nums[i] == 0) {
                return false;
            }
            int index[nums[i]];
            int max_index     = 0;
            int max_index_seq = 0;

            for(int k = 0; k < nums[i]; k++) {
                if(i+k+1 < nums.size()) {
                    index[k] = i+k+1 + nums[i+k+1];
                    if(index[k] > max_index) {
                        max_index = index[k];
                        max_index_seq = k;
                    }
                } else {
                    return true;
                }
            }


            if(max_index >= nums.size()-1) {
                return true;
            }

            i = i + max_index_seq + 1;

        }

        return false;

    }
};

int canJump(){
//    std::vector<int> nums = {1,1,2,2,0,1,1};
//    std::vector<int> nums = {3,2,1,0,4};
    std::vector<int> nums = {2,3,1,1,4};

//    nums.push_back(2);
//    nums.push_back(3);
//    nums.push_back(1);
//    nums.push_back(1);
//    nums.push_back(4);
//    Solution solve;
//    printf("%d\n", solve.canJump(nums));
//    nums.push_back(2);
//    nums.push_back(0);
//    nums.push_back(0);
    Solution solve;
    printf("%d\n", solve.canJump(nums));
    return 0;
}
