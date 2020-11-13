//
// Created by Johnny on 2020/1/5.
//

#include "order_val_map.h"
void value_order_map() {
    order_val_map<int,double> id_time;
    clock_t start, finish;

    start = clock();
    double duration;

    for(int j = 0; j < 4; j++) {
        usleep(100000);
        finish = clock();
        duration = (double)(finish - start);
        id_time.insert(j,duration);

    }

    id_time.print();

    for(int j = 4; j < 8; j++) {
        usleep(100000);
        finish = clock();
        duration = (double)(finish - start);
        id_time.insert(j,duration);
        id_time.erase_head();
        id_time.print();

    }

    for(int j = 0; j < 4; j++) {
        usleep(100000);
        finish = clock();
        duration = (double)(finish - start);
        id_time.insert(j,duration);
    }
    id_time.print();

}