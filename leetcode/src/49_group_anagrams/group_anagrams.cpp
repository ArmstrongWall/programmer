//
// Created by Johnny on 2019/8/18.
//
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "group_anagrams.h"

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {

        std::map<std::string,std::vector<std::string>> anagrams;
        std::vector<std::vector<std::string>> result;

        for(auto &x : strs) {
            std::string str = x;
            std::sort(str.begin(),str.end());

            if(anagrams.find(str) == anagrams.end()) {//anagrams has no str
                anagrams.insert({str,{x}});
            } else {
                anagrams[str].push_back(x);
            }
        }
        for(auto &x : anagrams) {
            result.push_back(x.second);
        }
        return result;
    }
};