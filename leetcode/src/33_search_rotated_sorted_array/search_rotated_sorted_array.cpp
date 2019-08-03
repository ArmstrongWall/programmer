//
// Created by johnny on 7/27/19.
//
#include <vector>
#include <cstdio>

#include "search_rotated_sorted_array.h"

class Solution {
public:
    int search(std::vector<int>& nums, int target) {

        int begin = 0;
        int end   = nums.size() - 1;

        while (begin <= end) {
            int mid = (begin + end) / 2;
            if(target == nums[mid]) {
                return mid;
            } else if(target < nums[mid]) {
                if(nums[begin] < nums[mid]) {
                    if(target >= nums[begin]) {
                        end = mid - 1;
                    } else {
                        begin = mid + 1;
                    }
                } else if(nums[begin] > nums[mid]) {
                    end = mid - 1;
                } else if(nums[begin] == nums[mid]) {
                    begin = mid + 1;
                }
            } else if(target > nums[mid]) {
                if(nums[begin] < nums[mid]) {
                    begin = mid + 1;
                } else if(nums[begin] > nums[mid]) {
                    if(target >= nums[begin]) {
                        end = mid - 1;
                    } else {
                        begin = mid + 1;
                    }
                } else if(nums[begin] == nums[mid]) {
                    begin = mid + 1;
                }
            }
        }

        return -1;

    }
};

int searchrotated(){
    Solution s;
    std::vector<int> sort_array = {4,5,6,7,0,1,2};

    int C = s.search(sort_array,0);
    printf("%d\n", C);

    return 0;
}