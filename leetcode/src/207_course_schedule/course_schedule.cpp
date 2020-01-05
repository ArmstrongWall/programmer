//
// Created by johnny on 7/13/19.
//
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