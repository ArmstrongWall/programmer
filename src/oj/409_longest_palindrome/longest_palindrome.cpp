//
// Created by Johnny on 2019/8/4.
//
#include <string>
#include "longest_palindrome.h"

class Solution {
public:
    int longestPalindrome(std::string s) {

        int char_map[128] = {0};
        int max_length    = 0;
        int flag          = 0;


        for(auto &x : s) {
            char_map[x]++;
        }

        for(auto &x : char_map) {
            if(x % 2 == 0) {
                max_length += x;
            } else {
                max_length += x - 1;
                flag        = 1;
            }
        }
        return max_length + flag;

    }
};