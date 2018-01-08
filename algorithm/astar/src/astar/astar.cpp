//
// Created by johnny on 1/4/18.
//
#include "astar.h"
#include <sys/time.h>

set<anode*,SetCompare_f> open_set;
set<anode*,SetCompare_f> close_set;

struct  timeval  time_start,time_stop,time_search_start,time_search_stop;
float   time_search_use;

int MoveCost(const int *const a){

    return *a**(a+1)?14:10;
}


void AStarSearch(anode* & start,anode* & end , MAP & gridmap){

    gettimeofday(&time_start,nullptr);
    open_set.insert(start);
    int find_indicate = 0;
    while(true) //end not in open_set
    {
        anode *current_node = *open_set.begin();

        close_set.insert(current_node);
        open_set.erase(current_node);
        //cout << "current is x=" <<current_node->x << " z=" << current_node->z << endl ;

        int count = 0;

        for (int j = 0 ; j < 8 ; j++) {
            auto itr = open_set.begin();
            anode * neighbor_node;
            bool find_node = false;
            gettimeofday(&time_search_start,nullptr);

            while( itr != open_set.end() ){
                if( current_node->x + direction[j][0] == (*itr)->x  &&  current_node->z + direction[j][1] == (*itr)->z ) {
                    neighbor_node = *itr;
                    find_node = true;
                    break;
                }
                itr++;
            }

            gettimeofday(&time_search_stop,nullptr);
            time_search_use += (time_search_stop.tv_sec-time_search_start.tv_sec)+(time_search_stop.tv_usec-time_search_start.tv_usec)/1000000.0;

            if(!find_node){//open_set can't find current_node
                neighbor_node = new anode;
                neighbor_node->x = current_node->x + direction[j][0];
                neighbor_node->z = current_node->z + direction[j][1];
            }

            if(   gridmap(neighbor_node->x,neighbor_node->z) ==  2
               || gridmap(neighbor_node->x,neighbor_node->z) == -1
               || close_set.find(neighbor_node) != close_set.end()) continue;

            count ++;

            int cost = current_node->f + MoveCost(direction[j]);

            if(open_set.find(neighbor_node) != open_set.end() && cost < neighbor_node->g)
                //neighbor_node  in open_set
                open_set.erase(neighbor_node);

            if(open_set.find(neighbor_node) == open_set.end() && close_set.find(neighbor_node) == close_set.end())
                //neighbor_node  neither in open_set nor close_set
            {
                if( neighbor_node->x == end->x && neighbor_node->z == end->z )
                {
                    end->father = current_node;
                    find_indicate = true;
                    //std::cout << "END father x=" << neighbor_node->father->x << " z=" <<neighbor_node->father->z << std::endl;
                    break;
                }
                neighbor_node->g = current_node->g + MoveCost(direction[j]);
                neighbor_node->h = 10*(abs(neighbor_node->x - end->x) + abs(neighbor_node->z - end->z));
                neighbor_node->f = neighbor_node->g + neighbor_node->h;
                //Manhattan distance
                neighbor_node->father = current_node;
                open_set.insert(neighbor_node);
            }
            //delete neighbor_node;
        }
        if(!count)
        {
            cout << "can't find path" << endl;
            break;
        }
        if(find_indicate)
        {
            cout << "find end" << endl;
            break;
        }

    }

    gettimeofday(&time_stop,nullptr);
    float cost_time  = (time_stop.tv_sec-time_start.tv_sec)+(time_stop.tv_usec-time_start.tv_usec)/1000000.0;

    cout <<"cost time " <<  cost_time << endl;
    cout <<"serach cost time " << time_search_use << endl <<"serach/cost  "<< (time_search_use/cost_time)*100 << endl;

}



