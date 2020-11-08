//
// Created by johnny on 6/15/19.
//

#include <vector>
#include <iostream>
#include "subsets.h"


/*
 *
 * 78. 子集
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: nums = [1,2,3]
输出:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


class Solution {
public:
    std::vector<std::vector<int>> subset_get(std::vector<int> &nums) {

        std::vector<std::vector<int>> all_sub;
        if(nums.empty()) {
            return all_sub;
        } else if(nums.size() == 1) {
            std::vector<int> seq{nums[0]};
            all_sub.push_back(seq);
            return all_sub;
        }

        auto it = nums.begin();

        std::vector<int> nums_remove_first;

        for(auto &x : nums) {
            if (x != *it) {
                nums_remove_first.push_back(x);
            }
        }
        all_sub = subset_get(nums_remove_first);

        std::vector<std::vector<int>> temp_all_sub(all_sub);

        for(auto &x : temp_all_sub) {
            std::vector<int> seq(x);
            seq.push_back(*it);
            all_sub.push_back(seq);
        }

        std::vector<int> seq{*it};
        all_sub.push_back(seq);
        return all_sub;
    }

    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        std::vector<std::vector<int>> all_sub;
        all_sub = subset_get(nums);
        all_sub.push_back({});
        return all_sub;
    }

    std::vector<std::vector<int>> subset_get_back(std::vector<int> &nums) {

        std::vector<int> items;
        std::vector<std::vector<int>> result;
        result.push_back(items);
        back_generate(0,items,nums,result);

        return result;

    }

    void back_generate(int i,
                       std::vector<int> &items,
                       std::vector<int> &nums,
                       std::vector<std::vector<int>> &result) {

        if(i >= nums.size()) {
            return;
        }


        items.push_back(nums[i]);
        result.push_back(items);
        back_generate(i+1, items, nums, result);

        items.pop_back();
        back_generate(i+1, items, nums, result);


    }

    std::vector<std::vector<int>> subsets_bit(std::vector<int> &nums) {
        std::vector<std::vector<int>> result;

        int all_set_count = 1 << nums.size();

        for(int i = 0; i< all_set_count; i++) {
            std::vector<int> item;
            for(int j = 0; j < nums.size(); j++) {
                if( i & (1 << j) ) {
                    item.push_back(nums[j]);
                }
            }
            result.push_back(item);
        }
        return result;
    }


};

void subsets() {
    Solution s;
    std::vector<int> nums {1,2,3};
//    std::vector<std::vector<int>> all_sub = s.subsets(nums);
    std::vector<std::vector<int>> all_sub = s.subset_get_back(nums);
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