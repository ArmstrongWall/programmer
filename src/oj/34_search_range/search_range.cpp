//
// Created by johnny on 7/27/19.
//
#include <vector>
#include <cstdio>
#include "search_range.h"


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