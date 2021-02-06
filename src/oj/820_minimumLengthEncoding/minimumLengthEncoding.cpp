/**
* This file is part of programmer.
* Description: 
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* programmer is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* programmer is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with programmer. If not, see <http://www.gnu.org/licenses/>.
*
* @file        minimumLengthEncoding.cpp.c
* @brief       Defines the 
* @author      Ziqiang Wang
* @email       1531651@tongji.edu.cn
* @date        2021/2/6
* @copyright   Copyright (c) 2021
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2021/2/6    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*/

/*单词数组 words 的 有效编码 由任意助记字符串 s 和下标数组 indices 组成，且满足：

words.length == indices.length
        助记字符串 s 以 '#' 字符结尾
        对于每个下标 indices[i] ，s 的一个从 indices[i] 开始、到下一个 '#' 字符结束（但不包括 '#'）的 子字符串 恰好与 words[i] 相等

        给你一个单词数组 words ，返回成功对 words 进行编码的最小助记字符串 s 的长度 。



示例 1：

输入：words = ["time", "me", "bell"]
输出：10
解释：一组有效编码为 s = "time#bell#" 和 indices = [0, 2, 5] 。
words[0] = "time" ，s 开始于 indices[0] = 0 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[1] = "me" ，s 开始于 indices[1] = 2 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[2] = "bell" ，s 开始于 indices[2] = 5 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"

示例 2：

输入：words = ["t"]
输出：2
解释：一组有效编码为 s = "t#" 和 indices = [0] 。



提示：

1 <= words.length <= 2000
1 <= words[i].length <= 7
words[i] 仅由小写字母组成

        来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/short-encoding-of-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "minimumLengthEncoding.h"

using namespace std;

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words)
    {
        set<string> bag;
        for (auto& word : words) {
            reverse(word.begin(), word.end());
            bag.insert(word);
        }

        auto index = bag.begin();
        int  count = 0;
        for (;;) {
            if (index == --bag.end()) {
                count += index->size() + 1;
                break;
            }
            auto s1 = *index;
            auto s1Count = index->size();
            ++index;
            auto s2 = *index;

            if (!IsTailSame(s1, s2)) {
                count += s1Count + 1;
            }
        }

        // std::cout << "res" << count;
        return count;
    }
    bool IsTailSame (const string& word1, const string& word2)
    {
        // std::cout << "word1: " << word1 << " ,word2: " << word2 << "\n";

        for (int i = 0; i < min(word1.size(), word2.size()); ++i) {
            if (word1[i] != word2[i]) {
                return false;
            }
        }
        return true;
    }
};