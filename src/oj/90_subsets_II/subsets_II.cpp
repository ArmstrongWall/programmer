//
// Created by johnny on 6/29/19.
//
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include "subsets_II.h"


/*
 *
 * 90. 子集 II
 *
 * 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: [1,2,2]
输出:
[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {

        std::vector<int> items;
        std::set<std::vector<int>> result;

        std::sort(nums.begin(),nums.end());

        result.insert(items);
        back_generate(0,items,nums,result);


        std::vector<std::vector<int>> result_back;

        for(auto &x : result) {
            result_back.push_back(x);
        }

        return result_back;

    }

    void back_generate(int i,
                       std::vector<int> &items,
                       std::vector<int> &nums,
                       std::set<std::vector<int>> &result) {

        if(i >= nums.size()) {
            return;
        }

        items.push_back(nums[i]);
        result.insert(items);
        back_generate(i+1, items, nums, result);

        items.pop_back();
        back_generate(i+1, items, nums, result);


    }

};

void subsetsII() {
    Solution s;
    std::vector<int> nums {2,1,2,2};
//    std::vector<std::vector<int>> all_sub = s.subsets(nums);
    std::vector<std::vector<int>> all_sub = s.subsetsWithDup(nums);
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
