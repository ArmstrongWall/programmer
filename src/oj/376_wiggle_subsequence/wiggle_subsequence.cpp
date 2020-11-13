//
// Created by johnny on 6/15/19.
//
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