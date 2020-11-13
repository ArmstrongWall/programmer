#include <iostream>
#include <fstream>
#include "astar/astar.h"

enum{ LENGTH = 50, WIDE = 50 };
char printmap[LENGTH][WIDE];

int main()
{
    std::cout << "Hello, World!" << std::endl;
//make map
    auto grid_map = new MAP;
    auto start = new node;
    auto end   = new node;

    ifstream fin;
    fin.open("datatest3.txt");
    if (!fin.is_open())
    {
        cout << "Failed to open file!" << endl;
        return 0;
    }
    for (int i = 0; i< LENGTH; i++)
    {
        for (int j = 0; j< WIDE; j++)
        {
            char terrain;
            fin >> terrain;
            printmap[i][j]=terrain;

            switch (terrain)
            {
                case '.'://pass = 1
                    grid_map->gridInsertNode(i,j);
                    break;
                case 'x'://obstacle = 2
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    break;
                case 's'://start = 3
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    start->x = i;
                    start->z = j;
                    //start->used = true;
                    break;
                case 'd'://end = 4
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    grid_map->gridInsertNode(i,j);
                    end->x = i;
                    end->z = j;
                    break;
                default:;
            }
        }
        fin.get();
    }
    fin.close();

    std::cout << "inverse path is "<< std::endl;

    AStarSearch(grid_map->g_map.find(*start)->first,grid_map->g_map.find(*end)->first,*grid_map);

    std::cout << "end is "<< std::endl;
//
//    auto current_node = end;
//
//    std::cout << "inverse path is "<< std::endl;
//    auto itr = open_set.begin();
//    while( itr != open_set.end() )
//    {
//        printmap[(*itr)->x][(*itr)->z] = '^';
//        itr++;
//    }
//
    node current_node = *end;
    while( true )
    {
        if(current_node == *start)break;
        //std::cout << "x=" << current_node->x + 1<< "  z=" <<current_node->z +1<< std::endl;
        current_node = come_from[current_node];
        printmap[current_node.x][current_node.z] = '@';



    }

    for (int i = 0; i< LENGTH; i++) {
        for (int j = 0; j < WIDE; j++) {

            std::cout << printmap[i][j] ;
        }
        cout << endl;
    }


    return 1;
}
