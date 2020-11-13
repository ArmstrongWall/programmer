//
// Created by johnny on 6/15/19.
//
#include <vector>
#include <cstdio>
#include <algorithm>
#include "assign_cookies.h"


class Solution {
public:
    int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
        if(g.empty() || s.empty()) {
            return 0;
        }

        std::sort(g.begin(),g.end());
        std::sort(s.begin(),s.end());

        int child   = 0;
        int cookies = 0;

        while(child < g.size() && cookies < s.size()) {
            if(g[child] <= s[cookies]) {
                child++;
            }
            cookies++;
        }

        return child;
    }
};

int findContentChildren() {
    Solution solve;
    std::vector<int> g;
    std::vector<int> s;
    g.push_back(5);
    g.push_back(10);
    g.push_back(2);
    g.push_back(9);
    g.push_back(15);
    g.push_back(9);
    s.push_back(6);
    s.push_back(1);
    s.push_back(20);
    s.push_back(3);
    s.push_back(8);
    printf("%d\n", solve.findContentChildren(g, s));
    return 0;
}
