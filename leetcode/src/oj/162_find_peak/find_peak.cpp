//
// Created by johnny on 6/23/19.
//
#include <vector>
#include <cstdio>

#include "find_peak.h"

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