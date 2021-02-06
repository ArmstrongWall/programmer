/**
* This file is part of programmer.
* Description: 
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* programmer is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* programmer is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with programmer. If not, see <http://www.gnu.org/licenses/>.
*
* @file        binary_heap.h
* @brief       Defines the 
* @author      Ziqiang Wang
* @email       1531651@tongji.edu.cn
* @date        2021/1/8
* @copyright   Copyright (c) 2021
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2021/1/8    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*/

#ifndef LEETCODE_BINARY_HEAP_H
#define LEETCODE_BINARY_HEAP_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class BinaryHeap{

public:
    explicit BinaryHeap(unsigned long capacity = 1 );
    explicit BinaryHeap( const vector<T> & items );
    void isEmpty() const ;

    void insert(const T & x);
    void deletMin();
    void deletMin(T & item);
    void makeEmpty();
    void printBinaryHeap();
    void printBinaryHeap(const T &node,const unsigned long & index);

private:
    unsigned long currentSize;
    vector<T> array;
    void buildHeap();
    void percolateDown(int hole);

};

void BinaryHeapDemo();


#endif //LEETCODE_BINARY_HEAP_H
