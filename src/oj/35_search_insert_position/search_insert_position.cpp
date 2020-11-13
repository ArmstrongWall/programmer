//
// Created by johnny on 7/21/19.
//
#include <vector>
#include <cstdio>
#include "search_insert_position.h"


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