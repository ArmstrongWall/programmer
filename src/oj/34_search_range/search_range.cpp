//
// Created by johnny on 7/27/19.
//
#include <vector>
#include <cstdio>
#include "search_range.h"


/*给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？



示例 1：

输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]

示例 2：

输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]

示例 3：

输入：nums = [], target = 0
输出：[-1,-1]



提示：

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums 是一个非递减数组
-109 <= target <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) {

        if(nums.empty() || target < nums[0]) {
            return {-1,-1};
        } else if(target > nums[nums.size()-1]) {
            return {-1,-1};
        }

        std::vector<int> res;
        res.push_back(left_bound(nums,target));
        res.push_back(right_bound(nums,target));
        return res;

    }

    int left_bound(std::vector<int>& nums, int target) {
        int begin = 0;
        int end   = nums.size()-1;
        int mid   = (begin + end)/2;

        while (begin <= end) {
            if(nums[mid] == target) {
                if(mid == 0)
                    return 0;
                else if(nums[mid] > nums[mid - 1]) {
                    return mid;
                }
                mid--;
            } else {
                mid = (begin + end)/2;
                if(target > nums[mid]) {
                    begin = mid + 1;
                } else if(target < nums[mid]) {
                    end   = mid - 1;
                }
            }
        }
        return -1;
    }

    int right_bound(std::vector<int>& nums, int target) {
        int begin = 0;
        int end   = nums.size() - 1;
        int mid   = (begin + end)/2;

        while (begin <= end) {
            if(nums[mid] == target) {
                if(mid == nums.size() - 1)
                    return nums.size() - 1;
                else if(nums[mid] < nums[mid + 1]) {
                    return mid;
                }
                mid++;
            } else {
                mid = (begin + end)/2;
                if(target > nums[mid]) {
                    begin = mid + 1;
                } else if(target < nums[mid]) {
                    end   = mid - 1;
                }
            }
        }
        return -1;
    }
};