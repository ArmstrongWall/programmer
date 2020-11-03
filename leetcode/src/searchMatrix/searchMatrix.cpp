//
// Created by Johnny on 2020/11/3.
//
#include <vector>
#include <iostream>
#include "searchMatrix.h"

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {

        if(matrix.empty()) {
            return false;
        }
        if(matrix[0].empty()) {
            return false;
        }
        int i_max= matrix.size() - 1;
        int j_max = matrix[0].size() - 1;

        if(target > matrix[i_max][j_max] || target < matrix[0][0]) {
            return false;
        }

        for(int i = 0; i <= i_max; i++) {
            int begin = 0;
            int end   = j_max;
            while(begin <= end) {
                int middle = (begin + end)/2;
                if(matrix[i][middle] == target) {
                    return true;
                } else if(matrix[i][middle] > target) {
                    end   = middle - 1;
                    j_max = end;
                } else if(matrix[i][middle] < target) {
                    begin =  middle + 1;
                }
            }
        }
        return false;


    }
};

int searchMatrix() {
    std::vector<std::vector<int>> matrix =
      { {15, 30,  50,  70,  73},
        {35, 40, 100, 102, 120},
        {36, 42, 105, 110, 125},
        {46, 51, 106, 111, 130},
        {48, 55, 109, 140, 150} };
//    std::vector<std::vector<int>> matrix =
//            { {1, 1}};

    Solution s;
    std::cout << s.searchMatrix(matrix,42);


}