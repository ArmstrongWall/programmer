//
// Created by johnny on 6/23/19.
//

/*
402. 移掉K位数字
https://leetcode-cn.com/problems/remove-k-digits/
        给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:

num 的长度小于 10002 且 ≥ k。
num 不会包含任何前导零。

示例 1 :

输入: num = "1432219", k = 3
输出: "1219"
解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

示例 2 :

输入: num = "10200", k = 1
输出: "200"
解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

示例 3 :

输入: num = "10", k = 2
输出: "0"
解释: 从原数字移除所有的数字，剩余为空就是0。

*/


#include <vector>
#include <stack>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include "remove_k_dig.h"

class Solution {
public:
    std::string removeKdigits(std::string num, int k) {

        if(num.empty() || num.size() == 1 || num.size() == k) {
            return "0";
        }

        int delete_time = 0;
        int origin_size = num.size();
        std::vector<unsigned char> stack_num;

        stack_num.push_back(num[0]);

        for(int i = 1; i < num.size(); i++) {

            while(!stack_num.empty() && num[i] < stack_num.back() && delete_time != k) {
                delete_time ++;
                stack_num.pop_back();
            }

            if(!stack_num.empty() && stack_num.back() == '0' && stack_num.size() == 1){
                stack_num.pop_back();
            }

            stack_num.push_back(num[i]);
        }

        if(delete_time < k) {
            for(int j = k - delete_time; j > 0 ; j--) {
                stack_num.pop_back();
            }
        }

        num.clear();
        for(auto &x : stack_num) {
            num.push_back(x);
        }


        return num;
    }

};

class Solution1 {
public:
    std::string removeKdigits(std::string num, int k) {

        if(num.empty() || num.size() == 1 || num.size() == k) {
            return "0";
        }

        int delete_time = 0;
        int origin_size = num.size();
        std::stack<unsigned char> stack_num;

        stack_num.push(num[0]);

        for(int i = 1; i < num.size(); i++) {

            while(!stack_num.empty() && num[i] < stack_num.top() && delete_time != k) {
                delete_time ++;
                stack_num.pop();
            }

            if(!stack_num.empty() && stack_num.top() == '0' && stack_num.size() == 1){
                stack_num.pop();
            }

            stack_num.push(num[i]);
        }

        if(delete_time < k) {
            for(int j = k - delete_time; j > 0 ; j--) {
                stack_num.pop();
            }
        }
        store_num(num,stack_num);


        return num;
    }

    void store_num(std::string &num,std::stack<unsigned char> &stack_num){

        num.clear();
        while(!stack_num.empty()) {
            num.push_back(stack_num.top());
            stack_num.pop();
        }
        reverse(num.begin(),num.end());
    }



};

int removeKdigits(){
//    Solution solve;
//    std::string result = solve.removeKdigits("11226673",2);
//    printf("%s\n", result.c_str());
    Solution solve1;
    std::string result2 = solve1.removeKdigits("1432219", 3);
    printf("%s\n", result2.c_str());
    return 0;
}
