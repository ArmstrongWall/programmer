//
// Created by johnny on 1/4/18.
//

#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

static const int direction[8][2] = {
        { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
        {  0,  1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };// 方向

struct anode
{
    int    x        = 0;
    int    z        = 0;
    int    f        = 0;
    int    g        = 0;
    int    h        = 0;
    anode* father   = nullptr;
    //bool   used     = false;
};

class SetCompare_f
{
public:

    bool operator() ( const anode *x, const anode *y ) const
    {
        return (        x->f <  y->f
                    ||  x->f == y->f && x->x <  y->x
                    ||  x->f == y->f && x->x == y->x && x->z < y->z );
    }
};

extern set<anode*,SetCompare_f> open_set;
extern set<anode*,SetCompare_f> close_set;


struct node
{
    int x;
    int z;
    bool operator < (const node &compNode) const
    {
        return (this->x < compNode.x || (this->x == compNode.x && this->z < compNode.z));
    }
};

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
        node temp_n;
        temp_n.x = x;
        temp_n.z = z;
        if(g_map.find(temp_n) == g_map.end())//no this node
        {
            g_map[temp_n] = 1;//add node
        }
        else//already have this node
        {
            g_map[temp_n]++;//point cloud num ++
        }
    }


    map<node, int> g_map;
    set<globalVertex> vertex_map;

    int error;

    int  &operator ()(int x, int z)
    {
        node temp_n;
        temp_n.x = x;
        temp_n.z = z;

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

void AStarSearch(anode* & start,anode* & end, MAP & gridmap);
#endif //ASTAR_ASTAR_H
