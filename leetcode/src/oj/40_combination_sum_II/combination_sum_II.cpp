//
// Created by johnny on 6/30/19.
//
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "combination_sum_II.h"

class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {

        std::vector<int> items;
        std::set<std::vector<int>> result;

        std::sort(candidates.begin(),candidates.end());

        back_generate(0,target,0,items,candidates,result);


        std::vector<std::vector<int>> result_back;

        for(auto &x : result) {
            result_back.push_back(x);
        }

        return result_back;

    }

    void back_generate(int i,int target,int sum,
                       std::vector<int> &items,
                       std::vector<int> &nums,
                       std::set<std::vector<int>> &result) {

        if(i >= nums.size() || sum > target) {
            return;
        }

        items.push_back(nums[i]);
        sum += nums[i];
        if(sum == target) {
            result.insert(items);
        }
        back_generate(i+1, target, sum, items, nums, result);

        sum -= nums[i];
        items.pop_back();
        back_generate(i+1, target, sum, items, nums, result);


    }
};

void combinationSum2() {
    Solution s;
    std::vector<int> nums {10,1,2,7,6,1,5};//2,5,2,1,2
    std::vector<int> nums1 {2,5,2,1,2};//

//    std::vector<std::vector<int>> all_sub = s.subsets(nums);
    std::vector<std::vector<int>> all_sub = s.combinationSum2(nums1,5);
    std::cout << "sub size = " << all_sub.size() << "\n";

    int i = 0;
    for(auto &x : all_sub) {
        std::cout << "\nsub:" << i << ", has elements [" << "";
        for(auto &ele : x) {
            std::cout << ele << ",";
        }
        std::cout << "]";
        i++;
    }


}