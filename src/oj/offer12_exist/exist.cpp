//
// Created by Johnny on 2020/11/8.
//

#include <vector>
#include <string>
#include "exist.h"

/*
剑指 Offer 12. 矩阵中的路径
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。



示例 1：

输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

提示：

1 <= board.length <= 200
1 <= board[i].length <= 200

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

using namespace std;

class Solution {
public:

    bool match_word(vector<vector<char>>& board, string word,
                    int& word_index, vector<vector<bool>>& reach,
                    int row, int col, int i, int j) {


        if(word_index == word.size()) {
            return true;
        }
        bool find_next = false;

        // std::cout << "\n this is:" << board[i][j] <<",i:"<< i <<",j:" <<j;
        if( i >= 0 && i < row && j >= 0 && j < col
            && board[i][j] == word[word_index] && !reach[i][j]) {
            word_index++;
            reach[i][j] = true;
            //std::cout << "\n to find next:" << word_index;

            find_next =
                    match_word(board,word,word_index,reach,row,col,i-1,j) ||
                    match_word(board,word,word_index,reach,row,col,i+1,j) ||
                    match_word(board,word,word_index,reach,row,col,i,j-1) ||
                    match_word(board,word,word_index,reach,row,col,i,j+1);

            if(!find_next) {
                word_index--;
                reach[i][j] = false;
            }
        }
        return find_next;
    }
    bool exist(vector<vector<char>>& board, string word) {

        if (!word.size())
            return true;

        int row = board.size();
        int col = board[0].size();
        // std::cout << row << "," << col;
        bool has_find = false;

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {

                if(board[i][j] == word[0]) {
                    //std::cout << "\nfind 0:" << board[i][j] <<",i:"<< i <<",j:" <<j;

                    vector<vector<bool>> reach(row,vector<bool>(col,false));
                    int word_index = 0;
                    if(match_word(board,word,word_index,reach,row,col,i,j)) {
                        return true;
                    }
                }
            }
        }
        return false;

    }
};