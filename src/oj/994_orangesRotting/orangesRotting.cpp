//
// Created by wzq on 2020/11/18.
//

/*
 * 994. 腐烂的橘子
 * 在给定的网格中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。

每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。



示例 1：

输入：[[2,1,1],[1,1,0],[0,1,1]]
输出：4

示例 2：

输入：[[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。

示例 3：

输入：[[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。



提示：

1 <= grid.length <= 10
1 <= grid[0].length <= 10
grid[i][j] 仅为 0、1 或 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotting-oranges
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <queue>
#include <vector>
#include <iostream>
#include "orangesRotting.h"

using namespace std;
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {

        vector<vector<int>>   visited(grid.size(),vector<int>(grid[0].size(),0));
        vector<vector<int>>   cnt(grid.size(),vector<int>(grid[0].size(),0));
        queue<pair<int,int>>  bad_apple;
        vector<pair<int,int>> dir{make_pair(0,1),make_pair(0,-1),make_pair(1,0),make_pair(-1,0)};

        int  good_num = 0;
        int  decreas = 0;
        bool print = false;

        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == 2) {
                    bad_apple.push(make_pair(i,j));
                    visited[i][j] = 1;
                } else if(grid[i][j] == 1) {
                    good_num++;
                } else if(grid[i][j] == 0) {
                    visited[i][j] = 1;
                }
                 if(print) cout << ",v[" << i << "][" << j << "]=" << visited[i][j];
            }
             if(print) cout << endl;
        }


        int i = 0, j = 0;
        while(!bad_apple.empty()) {
            auto temp_bad_apple = bad_apple.front();
            bad_apple.pop();
            i = temp_bad_apple.first;
            j = temp_bad_apple.second;

            if(print) cout << "now bad" << i << "," << j << endl;
            for(auto d : dir) {
                auto next_i = i + d.first;
                auto next_j = j + d.second;
                if(next_i >= 0 && next_i < grid.size() && next_j >= 0 && next_j < grid[0].size()) {
                    if(!visited[next_i][next_j] && grid[next_i][next_j] == 1) {
                        bad_apple.push(make_pair(next_i,next_j));
                        visited[next_i][next_j] = 1;
                        cnt[next_i][next_j]     = cnt[i][j] + 1;
                        decreas++;
                    }
                }
            }
        }

        return decreas == good_num ? cnt[i][j] : -1;

    }
};

