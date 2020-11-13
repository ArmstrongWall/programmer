//
// Created by johnny on 6/30/19.
//
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "combination_sum_II.h"

/*40. 组合总和 II
 *
 * 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：

所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。

示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
        所求解集为:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]

示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
        所求解集为:
[
[1,2,2],
[5]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

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