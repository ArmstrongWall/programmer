//
// Created by Johnny on 2019/8/18.
//

#include <string>
#include <map>
#include "word_pattern.h"

/*给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true

示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false

示例 3:

输入: pattern = "aaaa", str = "dog cat cat dog"
输出: false

示例 4:

输入: pattern = "abba", str = "dog dog dog dog"
输出: false

说明:
你可以假设 pattern 只包含小写字母， str 包含了由单个空格分隔的小写字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

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