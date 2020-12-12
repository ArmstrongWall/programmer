//
// Created by johnny on 6/30/19.
//

#include <string>
#include <vector>
#include <iostream>
#include "n_queens.h"

/*51. N 皇后
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。



示例：

输入：4
输出：[
[".Q..",  // 解法 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // 解法 2
"Q...",
"...Q",
".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。



提示：

皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

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
            for(int i = 1;; i++) {
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
    return 0;
}