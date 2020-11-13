//
// Created by johnny on 6/15/19.
//

/*376. 摆动序列
https://leetcode-cn.com/problems/wiggle-subsequence/
        如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。

例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。

示例 1:

输入: [1,7,4,9,2,5]
输出: 6
解释: 整个序列均为摆动序列。

示例 2:

输入: [1,17,5,10,13,15,10,5,16,8]
输出: 7
解释: 这个序列包含几个长度为 7 摆动序列，其中一个可为[1,17,10,13,10,16,8]。

示例 3:

输入: [1,2,3,4,5,6,7,8,9]
输出: 2*/

#include <vector>
#include <cmath>
#include <cstdio>
#include "wiggle_subsequence.h"

#define ADD 0
#define SUB 1
#define EQU 2
class Solution {
public:
    int wiggleMaxLength(std::vector<int>& nums) {
        if(nums.empty()) {
            return 0;
        } else if(nums.size() == 1 ) {
            return 1;
        } else if(nums.size() == 2 && nums[0] != nums[1]) {
            return 2;
        } else if(nums.size() == 2 && nums[0] == nums[1]) {
            return 1;
        }

        int wiggle_count = 1;
        int last_state   = EQU;
        int now_state    = 0;


        if(nums[0] < nums[1]) {
            wiggle_count++;
            last_state  = ADD;
        } else if(nums[0] > nums[1]) {
            wiggle_count++;
            last_state  = SUB;
        }

        for(int i = 2; i < nums.size(); i++) {

            if(nums[i] > nums[i-1]) {
                now_state  = ADD;
            } else if(nums[i] < nums[i-1]) {
                now_state  = SUB;
            } else {
                now_state  = EQU;
            }
            if((now_state == ADD && last_state == SUB)
               || (now_state == SUB && last_state == ADD)
               || (now_state == SUB && last_state == EQU)
               || (now_state == ADD && last_state == EQU)) {
                wiggle_count++;
                last_state = now_state;
            }
        }

        return wiggle_count;


    }
};

int wiggleMaxLength(){
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(17);
    nums.push_back(5);
    nums.push_back(10);
    nums.push_back(13);
    nums.push_back(15);
    nums.push_back(10);
    nums.push_back(5);
    nums.push_back(16);
    nums.push_back(8);

//    nums.push_back(1);
//    nums.push_back(1);
//    nums.push_back(7);
//    nums.push_back(4);
//    nums.push_back(9);
//    nums.push_back(2);
//    nums.push_back(5);

//    nums.push_back(1);
//    nums.push_back(2);
//    nums.push_back(3);
//    nums.push_back(4);
//    nums.push_back(5);
//    nums.push_back(6);
//    nums.push_back(7);

//    nums.push_back(1);
//    nums.push_back(4);
//    nums.push_back(4);
//    nums.push_back(5);


    Solution solve;
    printf("%d\n", solve.wiggleMaxLength(nums));
    return 0;
}