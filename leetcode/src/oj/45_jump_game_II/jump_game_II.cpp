//
// Created by johnny on 6/24/19.
//

#include <vector>
#include "jump_game_II.h"

class Solution {
public:
    int jump(std::vector<int>& nums) {

        if(nums.size() < 2) {
            return 0;
        }

        int current_max_index = 0;
        int farest_index      = 0;
        int jump_min          = 1;
        current_max_index     = nums[0];

        for(int i = 1; i < nums.size(); i++) {
            if(i > current_max_index) {
                jump_min++;
                current_max_index = farest_index;
            }
            if(farest_index < nums[i] + i) {
                farest_index      = nums[i] + i;
            }
        }

        return jump_min;
    }
};