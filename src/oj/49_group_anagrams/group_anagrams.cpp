//
// Created by Johnny on 2019/8/18.
//
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "group_anagrams.h"

/*给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
["ate","eat","tea"],
["nat","tan"],
["bat"]
]

说明：

所有输入均为小写字母。
不考虑答案输出的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/group-anagrams
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

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