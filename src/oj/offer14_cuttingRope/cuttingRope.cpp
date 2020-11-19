//
// Created by wzq on 2020/11/19.
//

/*
343. 整数拆分
        https://leetcode-cn.com/problems/integer-break/
        给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

说明: 你可以假设 n 不小于 2 且不大于 58。
*/

#include <vector>

#include "cuttingRope.h"

using namespace std;
class Solution {
public:
    int cuttingRope(int n) {


        if(n == 2) {
            return 1;
        }
        vector<int> dp(n+1,0);

        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 2;

        for(int i = 4; i <= n; i++) {
            int max = 1;
            for(int j = 1; j <= i/2; j++) {
                int left  = std::max(j,dp[j]);
                int right = std::max(i-j,dp[i-j]);
                if(left * right > max) {
                    max   = left * right;
                    dp[i] = max;
                }
            }
        }

        return dp[n];

    }
};