//
// Created by johnny on 7/13/19.
//

#include <vector>
#include <iostream>
#include <queue>

#include "graph_depth_first_search.h"


struct GraphNode {
    int label;
    std::vector<GraphNode*> neighbors;
    GraphNode(int l) : label(l) {};
};


void DFS_graph(GraphNode* gnode, int visit[]) {
    if(visit[gnode->label]) {
        return;
    }
    visit[gnode->label] = 1;
    printf("%d ", gnode->label);
    for(auto &x : gnode->neighbors) {
        if(!visit[x->label]) {
            DFS_graph(x,visit);
        }
    }

}

void BFS_graph(GraphNode* gnode, int visit[]) {

    if(visit[gnode->label]) {
        return;
    }

    std::queue<GraphNode*> Q;
    visit[gnode->label] = 1;
    printf("%d ", gnode->label);

    Q.push(gnode);

    while (!Q.empty()) {

        GraphNode* temp_node = Q.front();
        Q.pop();

        for(auto &x : temp_node->neighbors) {
            if(!visit[x->label]) {
                printf("%d ", x->label);
                visit[x->label] = 1;
                Q.push(x);
            }
        }
    }
}

int print_graph() {

    const int MAX_N = 5;

    GraphNode *Graph[MAX_N];
    for (int i = 0; i < MAX_N; i++){
        Graph[i] = new GraphNode(i);
    }

    Graph[0]->neighbors.push_back(Graph[4]);
    Graph[0]->neighbors.push_back(Graph[2]);
    Graph[1]->neighbors.push_back(Graph[0]);
    Graph[1]->neighbors.push_back(Graph[2]);
    Graph[2]->neighbors.push_back(Graph[3]);
    Graph[3]->neighbors.push_back(Graph[4]);
    Graph[4]->neighbors.push_back(Graph[3]);

    printf("DFS of graph\n");
    int visit[MAX_N] = {0};
    for (int i = 0; i < MAX_N; i++){
        if (visit[i] == 0){
            printf("From label(%d) : ", Graph[i]->label);
            DFS_graph(Graph[i], visit);
            printf("\n");
        }
    }

    printf("BFS of graph\n");
    int visit_bfs[MAX_N] = {0};
    for (int i = 0; i < MAX_N; i++){
        if (visit_bfs[i] == 0){
            printf("From label(%d) : ", Graph[i]->label);
            BFS_graph(Graph[i], visit_bfs);
            printf("\n");
        }
    }



    for (int i = 0; i < MAX_N; i++){
        delete Graph[i];
    }

    return 0;
}