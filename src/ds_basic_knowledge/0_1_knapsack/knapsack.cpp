//
// Created by wzq on 2020/11/12.
//
#include <vector>
#include <iostream>
#include "knapsack.h"
using namespace std;
void knapsack() {

    vector<int> value {0, 8, 10, 6, 3, 7, 2};
    vector<int> weight{0, 4,  6, 2, 2, 5, 1};
    int carry = 12;
    vector<vector<int>> dp(weight.size(),vector<int>(carry + 1, 0));

    for(int i = 1; i < dp.size(); i++) {
        for(int j = 1; j < dp[0].size(); j++) {

            if(weight[i] > j) {//当第i个物品重量w[i]大于此时包容量j时，必然选择不拿第i个物品，则去查dp[i-1][j]的值，
                dp[i][j] = dp[i-1][j];
            } else {
                //对于第i个物品选择拿，重量为w[i],原来包容量为j，此时剩余容量j-w[i]，去查前[i-1]个物品对应[j-w[i]]的值，再加上第i个物品的价值v[i]
                int choose    = dp[i-1][j-weight[i]] + value[i];
                //对于第i个物品选择不拿，此时剩余容量依然是j，去查前[i-1]个物品对应[j]的值
                int no_choose = dp[i-1][j];
                dp[i][j] = std::max(choose,no_choose);
            }

        }
    }

    for(int i = 1; i < dp.size(); i++) {
        cout << "no" << i << "row: ";
        for(int j = 1; j < dp[0].size(); j++) {
            cout << dp[i][j] << ",";
        }
        cout <<"\n";
    }

}