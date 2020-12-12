//
// Created by wzq on 2020/12/12.
//
#include <vector>
#include "n_queue_II.h"
using namespace std;

/*n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:

输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
[".Q..",  // 解法 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // 解法 2
"Q...",
"...Q",
".Q.."]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        std::vector<std::vector<int>> mark(n,std::vector<int>(n,0));
        row_putdown_queue(0,n,count,mark);
        return count;
    }
    void row_putdown_queue(const int now_row, const int n,
                           int &count, std::vector<std::vector<int>> &mark) {
        if(now_row == n) {
            count++;
            return;
        }


        for(int y = 0; y < n; y++) {
            if(mark[now_row][y] == 0) {
                std::vector<std::vector<int>> temp_mark = mark;
                queue_attack(mark, now_row, y, n);
                row_putdown_queue(now_row + 1, n, count, mark);
                mark = temp_mark;
            }
        }
    }

    void queue_attack(std::vector<std::vector<int>> &mark, const int x, const int y, const int n) {
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
};