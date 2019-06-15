//
// Created by johnny on 6/15/19.
//

#include <vector>
#include <iostream>
#include "subsets.h"
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
};

void subsets() {
    Solution s;
    std::vector<int> nums {1,2,3,4,5,6,7,8};
    std::vector<std::vector<int>> all_sub = s.subsets(nums);
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