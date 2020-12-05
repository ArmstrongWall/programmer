//
// Created by johnny on 7/21/19.
//
#include <vector>
#include <cstdio>
#include "search_insert_position.h"

/* https://leetcode-cn.com/problems/search-insert-position/
35. 搜索插入位置

        给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:

输入: [1,3,5,6], 5
输出: 2

示例 2:

输入: [1,3,5,6], 2
输出: 1

示例 3:

输入: [1,3,5,6], 7
输出: 4

示例 4:

输入: [1,3,5,6], 0
输出: 0

*/


class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {

        if(nums.empty() || target <= nums[0]) {
            return 0;
        } else if(target > nums[nums.size()-1]) {
            return nums.size();
        } else if(target == nums[nums.size()-1]) {
            return nums.size()-1;
        }

        return binary_serach(nums,0,nums.size()-1,target);


    }

    int binary_serach(std::vector<int>& nums, int begin, int end, int target) {
        if(end == begin + 1 && target > nums[begin] && target < nums[end]) {
            return begin + 1;
        }

        int mid = (begin + end) / 2;
        if(nums[mid] == target) {
            return mid;
        } else if(nums[mid] > target) {
            return binary_serach(nums,begin,mid,target);
        } else if(nums[mid] < target) {
            return binary_serach(nums,mid,end,target);
        }
        return 0;
    }
};

int searchInsert(){
    Solution s;
    int A[] = {1,3,5,6};
    std::vector<int> sort_array;
    int C;
    for (int i = 0; i < 4; i++){
        sort_array.push_back(A[i]);
    }
    C = s.searchInsert(sort_array,4);
    printf("%d\n", C);

    return 0;
}