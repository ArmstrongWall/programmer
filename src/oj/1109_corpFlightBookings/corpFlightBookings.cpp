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
* @file        corpFlightBookings.cpp.c
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

/*这里有 n 个航班，它们分别从 1 到 n 进行编号。

我们这儿有一份航班预订表，表中第 i 条预订记录 bookings[i] = [j, k, l] 意味着我们在从 j 到 k 的每个航班上预订了 l 个座位。

请你返回一个长度为 n 的数组 answer，按航班编号顺序返回每个航班上预订的座位数。



示例：

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]



提示：

1 <= bookings.length <= 20000
1 <= bookings[i][0] <= bookings[i][1] <= n <= 20000
1 <= bookings[i][2] <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/corporate-flight-bookings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include "corpFlightBookings.h"

#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n)
    {
        const int seatIndex = 2;
        vector<int> res(n, 0);
        for (auto &oneBook : bookings) {
            res[oneBook[0] - 1] += oneBook[seatIndex];
            if (oneBook[1] < n) {
                res[oneBook[1]] -= oneBook[seatIndex];
            }
        }
        for (int i = 1; i < res.size(); ++i) {
            res[i] += res[i - 1];
        }

        return res;
    }
};