//
// Created by Johnny on 2020/11/1.
//
#include<vector>
#include "rob.h"

/*
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
偷窃到的最高金额 = 2 + 9 + 1 = 12 。
*/

class Solution {
public:
    int rob(std::vector<int>& nums) {
        if(nums.empty())
            return 0;
        std::vector<int> dp(nums.size()+3,0);
        dp[1] = nums[0];
        if(nums.size() > 1) {
            dp[2] = std::max(nums[0],nums[1]);
        }

        if(nums.size() > 2) {
            for(int i = 3; i <= nums.size(); i++) {
                if(nums[i-1] + dp[i-2] > dp[i-1]) {
                    dp[i] = nums[i-1] + dp[i-2];
                } else {
                    dp[i] = dp[i-1];
                }
            }
        }
        return dp[nums.size()];
    }
};