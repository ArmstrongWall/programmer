//
// Created by johnny on 1/10/18.
//

#include <iostream>
#include <vector>
#include <map>
#include <list>


#ifndef DATASTRUCTUREALGORITHMANALYSISINCPP_AVLTREE_H
#define DATASTRUCTUREALGORITHMANALYSISINCPP_AVLTREE_H

/// @class order_val_map
/// \tparam Key
/// \tparam Value
template <typename Key, typename Value>
class order_val_map {
    std::map<Key, Value> m;
    std::list<Key>       key_l;

    void insert(Key k, Value v) {
        m[k] = v;
        auto it = std::list<Key>::begin();
        for(; it < key_l.end(); it++) {

        }
        key_l.insert(it);


    }

};











#endif //DATASTRUCTUREALGORITHMANALYSISINCPP_AVLTREE_H
