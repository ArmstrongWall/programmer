//
// Created by johnny on 6/23/19.
//
#include <vector>
#include <cstdio>

#include "find_peak.h"

/*峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞。

示例 1:

输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。

示例 2:

输入: nums = [1,2,1,3,5,6,4]
输出: 1 或 5
解释: 你的函数可以返回索引 1，其峰值元素为 2；
或者返回索引 5， 其峰值元素为 6。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-peak-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/



class Solution {
public:

    int findPeakElement(const std::vector<int> &num) {
        return Helper(num, 0, num.size()-1);
    }
    int Helper(const std::vector<int> &num, int low, int high)
    {
        if(low == high)
            return low;
        else
        {
            int mid1 = (low+high)/2;
            int mid2 = mid1+1;
            if(num[mid1] > num[mid2])
                return Helper(num, low, mid1);
            else
                return Helper(num, mid2, high);
        }
    }
};

int findPeak(){
//    std::vector<int> nums = {1,1,2,2,0,1,1};
//    std::vector<int> nums = {3,2,1,0,4};
    std::vector<int> nums = {1,2,1,3,5,6,4};

    Solution solve;
    printf("%d\n", solve.findPeakElement(nums));
    return 0;
}