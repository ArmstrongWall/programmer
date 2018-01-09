//
// Created by johnny on 1/4/18.
//
#include "astar.h"
#include <sys/time.h>

set<node> open_set;
set<node> close_set;
map<node,int> current_cost;
map<node,node> come_from;

//define a heap
template<typename T, typename priority_t>
struct PriorityQueue {
    typedef pair<priority_t, T> PQElement;
    priority_queue<PQElement, vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const { return elements.empty(); }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    inline T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

struct  timeval  time_start,time_stop;

//int MoveCost(const int *const a){
//
//    return *a**(a+1)?14:10;
//}
int MoveCost(const node & a){

    return a.x*a.z?14:10;
}

void AStarSearch(const node & start,const node & end , MAP & gridmap){

    gettimeofday(&time_start,nullptr);
    PriorityQueue< node, int> frontier;
    static const vector<node> direction = {
            { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
            {  0,  1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };

    open_set.insert(start);
    frontier.put(start, 0);
    current_cost[start] = 0;
    come_from[start] = start;


    while(!frontier.empty())
    {
        auto current_node = frontier.get();

        if(current_node == end) {
            cout << "find end" << endl;
            break;
        }

        open_set.erase(current_node);
        close_set.insert(current_node);

        for (auto index : direction) {
            //get neighbor_node
            auto neighbor_node = new node{current_node.x + index.x,current_node.z + index.z};

            if(   gridmap(neighbor_node->x,neighbor_node->z) ==  2  //neighbor_node is obstacle
               || gridmap(neighbor_node->x,neighbor_node->z) == -1  //no node in gridmap
               || close_set.find(*neighbor_node) != close_set.end()) continue;

            int cost = current_cost[current_node] + MoveCost(index);

            if(open_set.find(*neighbor_node) != open_set.end() && cost < current_cost[*neighbor_node]) {
                //neighbor_node  is already in open_set and ???
                open_set.erase(*neighbor_node);
                current_cost.erase(*neighbor_node);
            }


            if(open_set.find(*neighbor_node) == open_set.end() && close_set.find(*neighbor_node) == close_set.end())
                //neighbor_node  neither in open_set nor close_set
            {
                current_cost[*neighbor_node] = cost;//only store g
                int f = cost + 10*(abs(neighbor_node->x - end.x) + abs(neighbor_node->z - end.z));//h : Manhattan distance
                frontier.put(*neighbor_node, f);
                open_set.insert(*neighbor_node);
                come_from[*neighbor_node] = current_node;
            }
            delete neighbor_node;
        }
    }
    gettimeofday(&time_stop,nullptr);
    double cost_time  = (time_stop.tv_sec-time_start.tv_sec)+(time_stop.tv_usec-time_start.tv_usec)/1000000.0;

    cout <<"cost time " <<  cost_time << endl;
}
