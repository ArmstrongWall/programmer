//
// Created by johnny on 6/30/19.
//

#include <vector>
#include <string>
#include <iostream>

#include "generate_parentheses.h"
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        std::string item;
        generate(n,0,0,item,result);
        return result;
    }

    void generate(int n, int left, int right, std::string item, std::vector<std::string> &result) {

        if(left > n) {
            return;
        }
        if(item.size() == 2*n) {
            result.push_back(item);
            return;
        }

        item.push_back('(');
        generate(n,left + 1,right,item,result);

        if(left > right) {
            item.pop_back();
            item.push_back(')');
            generate(n,left,right + 1,item,result);
        }
    }
};

int generateParenthesis() {
    Solution s;
    std::vector<std::string> result;
    std::string item;

    result = s.generateParenthesis(3);

    int i = 0;
    for(auto &x : result) {
        std::cout << "\nsub:" << i << ", has elements ";
        std::cout << x  ;
        i++;
    }

    return 0;
}
