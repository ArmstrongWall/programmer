//
// Created by Johnny on 2020/11/7.
//

#include <string>
#include <iostream>
#include "replaceSpace.h"

/*请实现一个函数，把字符串 s 中的每个空格替换成"%20"。



示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."



限制：

0 <= s 的长度 <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

class Solution {
public:
    std::string replaceSpace(std::string s) {
        int space_count = 0;
        for(auto &c : s) {
            if(c == ' ') {
                space_count++;
            }
        }
        if(space_count == 0) {
            return s;
        }

        int new_length = s.size() + space_count*2;


        int i = s.size() - 1;
        int j = new_length - 1;

        s.resize(new_length);

        for(; i >= 0; i--) {
            std::cout << s[i] << "  ";
            if(s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            } else {
                s[j--] = s[i];
            }
        }

        return s;


    }
};