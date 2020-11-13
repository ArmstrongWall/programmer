//
// Created by Johnny on 2020/1/5.
//
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <cassert>
#include <ctime>
#include <zconf.h>

#ifndef DATASTRUCTUREALGORITHMANALYSISINCPP_ORDER_VAL_MAP_H
#define DATASTRUCTUREALGORITHMANALYSISINCPP_ORDER_VAL_MAP_H
/// @class order_val_map
/// \tparam Key
/// \tparam Value
template <typename Key, typename Value>
class order_val_map {
public:
    order_val_map()  = default;
    ~order_val_map() = default;

    void insert(Key k, Value v) {
        if(m.find(k) == m.end()) {
            key_l.push_back(k);
        } else {
            key_l.push_back(k);
            key_l.pop_front();
        }
        m[k] = v;
        assert(key_l.size() == m.size());
    }

    void erase_head() {
        m.erase(key_l.front());
        key_l.pop_front();
    }

    void print() {
        std::cout <<"order_val_map has:\n";
        for(auto &x: key_l) {
            std::cout << x << "->" << m[x] <<"\n";
        }
        std::cout <<"end order_val_map\n";
    }

private:
    std::map<Key, Value> m;
    std::list<Key>       key_l;


};



void value_order_map();
#endif //DATASTRUCTUREALGORITHMANALYSISINCPP_ORDER_VAL_MAP_H
