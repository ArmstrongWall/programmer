//
// Created by johnny on 6/30/19.
//

#include <string>
#include <vector>
#include <iostream>
#include "n_queens.h"

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::vector<int>> mark;
        std::vector<std::string>      location;

        for(int i = 0; i < n; i++) {
            std::vector<int> row;
            for(int j = 0; j < n; j++) {
                row.push_back(0);
            }
            location.push_back("");
            location[i].append(n,'.');
            mark.push_back(row);
        }

        generate(0,n,location,result,mark);

        return result;
    }

    void generate(int k, int n,
                  std::vector<std::string> &location,
                  std::vector<std::vector<std::string>> &result,
                  std::vector<std::vector<int>> &mark) {
        if(k == n) {
            result.push_back(location);
            return;
        }

        for(int i = 0; i < n; i++) {
            if(mark[k][i] == 0) {
                std::vector<std::vector<int>> temp_mark = mark;
                location[k][i] = 'Q';
                put_down_queen(mark,k,i,n);
                generate(k + 1, n, location, result, mark);
                mark = temp_mark;
                location[k][i] = '.';
            }
        }

    }

    void put_down_queen(std::vector<std::vector<int>> &mark, int x, int y, int n) {

        static const std::vector<std::pair<int,int>> direction = {
                { -1, -1 }, { -1,  0 }, { -1, 1 }, { 0, -1 },
                {  0,  1 }, {  1, -1 }, {  1, 0 }, { 1,  1 } };

        mark[x][y] = 1;

        for(auto &dir : direction) {
            for(int i = 1;; i++){
                if( x + i * dir.first >= n || y + i * dir.second >= n
                ||  x + i * dir.first < 0  || y + i * dir.second < 0) {
                    break;
                }
                mark[x + i * dir.first][y + i * dir.second] = 1;
            }
        }

    }

    void print_map(std::vector<std::vector<int>> &mark) {

        std::cout << "now map is\n";
        for(int i = 0; i < mark.size(); i++) {
            for(int j = 0; j < mark[i].size(); j++) {
                std::cout << mark[i][j] << ",";
            }
            std::cout << "\n";
        }
    }
};

int n_queen() {
    Solution s;
    s.solveNQueens(8);
}