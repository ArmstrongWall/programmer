#include <iostream>
#include <fstream>
#include "astar/astar.h"
enum{ LENGTH = 50, WIDE = 50 };
char printmap[LENGTH][WIDE];

int main()
{
    std::cout << "Hello, World!" << std::endl;
//make map
    MAP grid_map;
    auto * start = new anode;
    auto * end   = new anode;

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
            auto * temp_node = new node;
            char terrain;
            fin >> terrain;
            temp_node->x = i;
            temp_node->z = j;
            printmap[i][j]=terrain;

            switch (terrain)
            {
                case '.'://pass = 1
                    grid_map.gridInsertNode(i,j);
                    break;
                case 'x'://obstacle = 2
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    break;
                case 's'://start = 3
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    start->x = i;
                    start->z = j;
                    //start->used = true;
                    break;
                case 'd'://end = 4
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    grid_map.gridInsertNode(i,j);
                    end->x = i;
                    end->z = j;
                    //end->used = true;
                    break;
                default:;
            }
        }
        fin.get();
    }
    fin.close();

    AStarSearch(start,end,grid_map);

    auto current_node = end;

    std::cout << "inverse path is "<< std::endl;
    auto itr = open_set.begin();
    while( itr != open_set.end() )
    {
        printmap[(*itr)->x][(*itr)->z] = '^';
        itr++;
    }

    while( current_node )
    {
        printmap[current_node->x][current_node->z] = '@';
        //std::cout << "x=" << current_node->x + 1<< "  z=" <<current_node->z +1<< std::endl;
        current_node = current_node->father;
    }


    for (int i = 0; i< LENGTH; i++) {
        for (int j = 0; j < WIDE; j++) {

            std::cout << printmap[i][j] ;
        }
        cout << endl;
    }


    return 1;
}
