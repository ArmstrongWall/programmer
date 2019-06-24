//
// Created by johnny on 6/24/19.
//
#include <vector>
#include <cstdio>
#include <algorithm>

#include "burst_balloons.h"

bool cmp(const std::vector<int> &a, const std::vector<int> &b) {
    return a[0] < b[0];
}

class Solution {
public:
    int findMinArrowShots(std::vector<std::vector<int>>& points) {

        if(points.empty()) {
            return 0;
        } else if(points.size() == 1) {
            return 1;
        }
        std::sort(points.begin(), points.end(), cmp);

        std::pair<int,int> first_shoter = {points[0][0],points[0][1]};

        std::vector<std::pair<int,int>> shoters = {first_shoter};

        for(int i = 1; i < points.size(); i++) {

            bool find = false;
            for(auto & shot : shoters) {

                if(shot.first <= points[i][1] && shot.first > points[i][0] && shot.second >= points[i][1]) {
                    shot.second = points[i][1];
                    find = true;
                    break;
                } else if(shot.first <= points[i][0] && shot.second >= points[i][1]) {
                    shot.first  = points[i][0];
                    shot.second = points[i][1];
                    find = true;
                    break;
                } else if(shot.first >= points[i][0] && shot.second <= points[i][1]) {
                    find = true;
                    break;
                } else if(shot.second >= points[i][0] && shot.second <= points[i][1] && shot.first <= points[i][0]) {
                    shot.first  = points[i][0];
                    find = true;
                    break;
                }
            }
            if(!find) {
                shoters.push_back({points[i][0],points[i][1]});
            }
        }

        return shoters.size();

    }
};

int findMinArrowShots(){
    std::vector<std::vector<int> > points;
    points.push_back({3,9});
    points.push_back({7,12});
    points.push_back({3,8});
    points.push_back({6,8});
    points.push_back({9,10});
    points.push_back({2,9});
    points.push_back({3,9});
    points.push_back({0,6});
    points.push_back({2,8});
    Solution solve;
    printf("%d\n", solve.findMinArrowShots(points));
    return 0;
}