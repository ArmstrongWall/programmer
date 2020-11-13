//
// Created by johnny on 1/4/18.
//

#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <vector>
#include <map>
#include <queue>
#include <set>
#include <iostream>

using namespace std;


struct node
{
    int x;
    int z;
    bool operator < (const node &compNode) const
    {
        return (this->x < compNode.x || (this->x == compNode.x && this->z < compNode.z));
    }
    bool operator == (const node &compNode) const
    {
        return (this->x == compNode.x &&  this->z == compNode.z);
    }
    bool operator != (const node &compNode) const
    {
        return (this->x != compNode.x &&  this->z != compNode.z);
    }
};



extern set<node> open_set;
extern set<node> close_set;
extern map<node,node> come_from;

struct globalVertex
{
    float x;
    float y;
    float z;
    bool operator < (const globalVertex &compVertex) const
    {
        return (this->x <  compVertex.x
                || (this->x == compVertex.x && this->y <  compVertex.y)
                || (this->x == compVertex.x && this->y == compVertex.y && this->z < compVertex.z )
        );
    }
};


class MAP
{
    //friend ostream &operator<< (ostream&,const node&);
public:
    MAP()
    {
        error = -1;
    }
    void gridInsertNode(int x, int z)
    {
        auto temp_n = new node{x,z};

        if(g_map.find(*temp_n) == g_map.end())//no this node
        {
            g_map[*temp_n] = 1;//add node
        }
        else//already have this node
        {
            g_map[*temp_n]++;//point cloud num ++
        }
        delete temp_n;
    }


    map<node, int> g_map;
    set<globalVertex> vertex_map;

    int error;

    int  &operator ()(int x, int z)
    {
        node temp_n{x,z};
        if (g_map.find(temp_n) == g_map.end())//no this node
        {
            //cout << "no this node"<<endl;
            return error;
        }

        //cout << "x=" << x << " y=" << y << " num=" << r_map[temp_n] << endl;
        return g_map[temp_n];
    }
    void PrintMap()
    {
        map<node, int>::iterator itr;
        itr = g_map.begin();
        int i = 0;
        while(itr != g_map.end())
        {
            cout << "node " << i  <<", x= "<< itr->first.x
                 << ", z= " << itr->first.z
                 << ", point cloud =" << itr->second
                 << endl;
            itr++;
            i++;
        }

    }
};

void AStarSearch(const node & start,const node & end , MAP & gridmap);
#endif //ASTAR_ASTAR_H
