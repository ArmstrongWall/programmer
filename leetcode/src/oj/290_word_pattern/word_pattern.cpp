//
// Created by Johnny on 2019/8/18.
//

#include <string>
#include <map>
#include "word_pattern.h"

class Solution {
public:
    bool wordPattern(std::string pattern, std::string str) {

        int pattern_index = 0;
        int words_num     = 0;
        std::string word  = {};
        bool used[128]    = {false};
        std::map<std::string,char> pattern_word_map;
        str.push_back(' ');

        for(auto &x : str) {
            if(x == ' ') {
                if(words_num == pattern.size()) {
                    return false;
                }
                if(pattern_word_map.find(word) == pattern_word_map.end()) {//! word no appera
                    if(used[pattern[pattern_index]]) {
                        return false;
                    }

                } else {
                    if(pattern_word_map[word] != pattern[pattern_index]) {//! word appera
                        return false;
                    }
                }

                pattern_word_map[word] = pattern[pattern_index];
                used[pattern[pattern_index]] = true;
                word.clear();
                words_num ++;
                pattern_index ++;
            } else {
                word += x;
            }
        }

        return words_num == pattern.size();

    }
};