//
// Created by Johnny on 2019/12/15.
//

/*
 * 200. 岛屿数量
 * 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。



示例 1：

输入：grid = [
["1","1","1","1","0"],
["1","1","0","1","0"],
["1","1","0","0","0"],
["0","0","0","0","0"]
]
输出：1

示例 2：

输入：grid = [
["1","1","0","0","0"],
["1","1","0","0","0"],
["0","0","1","0","0"],
["0","0","0","1","1"]
]
输出：3



提示：

m == grid.length
        n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-islands
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <vector>
#include <queue>
#include <iostream>

#include "num_islands.h"

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {

        int island_num = 0;
        std::vector<std::vector<int>> mark;
        for(int x = 0; x < grid.size(); x++) {
            mark.emplace_back(std::vector<int>());
            for(int y = 0; y < grid[x].size(); y++) {
                mark[x].push_back(0);
            }
        }

        for(int x = 0; x < grid.size(); x++) {
            for(int y = 0; y < grid[x].size(); y++) {
                if(mark[x][y] == 0 && grid[x][y] == '1') {
                    DFS(grid,mark,x,y);
                    island_num++;
                }
            }
        }
        return island_num;

    }

    void DFS(std::vector<std::vector<char>>& grid,
             std::vector<std::vector<int>>& mark,
             int x, int y) {
        mark[x][y] = 1;
        static const int dx[] = {-1,1,0,0};
        static const int dy[] = { 0,0,1,-1};

        for(int i = 0; i < 4; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];

            if(new_x < 0 || new_x >= mark.size()
            || new_y < 0 || new_y >= mark[new_x].size()) {
                continue;
            }
            if(mark[new_x][new_y] == 0 && grid[new_x][new_y] == '1') {
                DFS(grid,mark,new_x,new_y);
            }
        }

    }
    void BFS(std::vector<std::vector<char>>& grid,
             std::vector<std::vector<int>>& mark,
             int x, int y) {
        static const int dx[] = {-1,1,0,0};
        static const int dy[] = { 0,0,1,-1};

        std::queue<std::pair<int,int>> work_que;
        work_que.push(std::make_pair(x,y));

        while (!work_que.empty()) {

            int now_x = work_que.front().first;
            int now_y = work_que.front().second;
            work_que.pop();
            for(int i = 0; i < 4; i++) {

                int new_x = now_x + dx[i];
                int new_y = now_y + dy[i];

                if(new_x < 0 || new_x >= mark.size()
                   || new_y < 0 || new_y >= mark[new_x].size()) {
                    continue;
                }
                if(mark[new_x][new_y] == 0 && grid[new_x][new_y] == '1') {
                    work_que.push(std::make_pair(new_x,new_y));
                    mark[new_x][new_y] = 1;
                }
            }
        }
    }
};

int numIslands() {
    std::vector<std::vector<char>> grid;
    char str[10][10] = {"11100","11000","00100","00011"};
    for(int x = 0; x < 4; x++) {
        grid.push_back(std::vector<char>());
        for(int y = 0; y < 5; y++) {
            grid[x].push_back(str[x][y]);
        }
    }

    Solution s;
    std::cout << s.numIslands(grid);

    return 0;
}
