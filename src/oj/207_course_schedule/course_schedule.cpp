//
// Created by johnny on 7/13/19.
//

/*
 * 你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？



示例 1:

输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。

示例 2:

输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。



提示：

输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。
1 <= numCourses <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/course-schedule
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <vector>
#include <iostream>
#include <queue>
#include "course_schedule.h"



class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        //return canFinish_dfs(numCourses,prerequisites);
        return canFinish_bfs(numCourses,prerequisites);

    }

private:
    bool canFinish_dfs(int numCourses, std::vector<std::vector<int>>& prerequisites) {

        const int MAX_N = numCourses;
        GraphNode* graph[MAX_N];
        std::vector<int> visit;

        for(int i = 0; i < MAX_N; i++) {
            graph[i] = new GraphNode(i);
            visit.push_back(-1);
        }

        for(auto prereq : prerequisites) {
            graph[prereq[1]]->neighbors.push_back(graph[prereq[0]]);
        }

        for(int i = 0; i < MAX_N; i++) {
            if(visit[i] == -1 && !DFS_graph(graph[i],visit)) {
                    return false;
            }
        }

        for(int i = 0; i < MAX_N; i++) {
            delete graph[i];
        }
        return true;
    }

    bool canFinish_bfs(int numCourses, std::vector<std::vector<int>>& prerequisites) {

        const int MAX_N = numCourses;
        GraphNode* graph[MAX_N];
        std::vector<int> degree;

        for(int i = 0; i < MAX_N; i++) {
            graph[i] = new GraphNode(i);
            degree.push_back(0);
        }

        for(auto prereq : prerequisites) {
            graph[prereq[1]]->neighbors.push_back(graph[prereq[0]]);
            degree[prereq[0]]++;
        }

        std::queue<GraphNode*> Q;

        for(int i = 0; i < numCourses; i++) {
            if(degree[i] == 0) {
                Q.push(graph[i]);
            }
        }


        while (!Q.empty()) {

            GraphNode* temp_node = Q.front();
            Q.pop();

            for(auto &neighbor : temp_node->neighbors) {
                degree[neighbor->label]--;
                if(degree[neighbor->label] == 0) {
                    Q.push(neighbor);
                }
            }
        }

        for(int i = 0; i < MAX_N; i++) {
            delete graph[i];
        }

        for(int i = 0; i < MAX_N; i++) {
            if(degree[i])
                return false;
        }

        return true;
    }


    struct GraphNode {
        int label;
        std::vector<GraphNode*> neighbors;
        GraphNode(int l) : label(l) {};
    };

    bool DFS_graph(GraphNode* gnode, std::vector<int> visit) {
        visit[gnode->label] = 0;
        for(auto &neighbor : gnode->neighbors) {
            if(visit[neighbor->label] == -1) {
                if(!DFS_graph(neighbor,visit)) {
                    return false;
                }
            } else if(visit[neighbor->label] == 0) {
                return false;
            }
        }
        visit[gnode->label] = 1;
        return true;
    }


};

int canFinish(){
    std::vector<std::vector<int>> prerequisites;
    prerequisites.push_back({1, 0});
    prerequisites.push_back({2, 0});
    prerequisites.push_back({3, 1});
    prerequisites.push_back({3, 2});
    Solution solve;
    printf("%d\n", solve.canFinish(4, prerequisites));
    return 0;
}