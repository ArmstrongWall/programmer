//
// Created by wzq on 2020/11/13.
//
/*
 *
 * https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4?tpId=37&&tqId=21239&rp=1&ru=/ta/huawei&qru=/ta/huawei/question-ranking
题目描述
        王强今天很开心，公司发给N元的年终奖。王强决定把年终奖用于购物，他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：

主件	附件
电脑	打印机，扫描仪
        书柜	图书
        书桌	台灯，文具
        工作椅	无

        如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 0 个、 1 个或 2 个附件。附件不再有从属于自己的附件。王强想买的东西很多，为了不超出预算，他把每件物品规定了一个重要度，分为 5 等：用整数 1 ~ 5 表示，第 5 等最重要。他还从因特网上查到了每件物品的价格（都是 10 元的整数倍）。他希望在不超过 N 元（可以等于 N 元）的前提下，使每件物品的价格与重要度的乘积的总和最大。
设第 j 件物品的价格为 v[j] ，重要度为 w[j] ，共选中了 k 件物品，编号依次为 j 1 ， j 2 ，……， j k ，则所求的总和为：
v[j 1 ]*w[j 1 ]+v[j 2 ]*w[j 2 ]+ … +v[j k ]*w[j k ] 。（其中 * 为乘号）
请你帮助王强设计一个满足要求的购物单。




输入描述:

输入的第 1 行，为两个正整数，用一个空格隔开：N m
（其中 N （ <32000 ）表示总钱数， m （ <60 ）为希望购买物品的个数。）


从第 2 行到第 m+1 行，第 j 行给出了编号为 j-1 的物品的基本数据，每行有 3 个非负整数 v p q


（其中 v 表示该物品的价格（ v<10000 ）， p 表示该物品的重要度（ 1 ~ 5 ）， q 表示该物品是主件还是附件。如果 q=0 ，表示该物品为主件，如果 q>0 ，表示该物品为附件， q 是所属主件的编号）




输出描述:

输出文件只有一个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值（ <200000 ）。

示例1
        输入
复制

1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0

输出
        复制

2200

*/



#include "get_things.h"


#include <vector>
#include <iostream>
using namespace std;
int get_things(void) {

    int carry      = 0;
    int thing_num  = 0;
    cin >> carry >> thing_num;
    vector<int> w,v,p;
    w.push_back(0);
    v.push_back(0);
    p.push_back(0);

    bool print = false;
    if(print) cout << "\n carry=" << carry << ",thing_num = " << thing_num;
    int a,b,c;
    int w_main_min = carry;
    while(cin >> a >> b >> c) {
        w.push_back(a);
        v.push_back(b);
        p.push_back(c);
        if(a < w_main_min) {
            w_main_min = a;
        }
    }
    if(print)  {
        cout << "\n w_main_min=" << w_main_min;
        for(int i = 0; i < w.size(); i++) {
            cout << "\n i=" << i << ", w = " << w[i] << ", v = " << v[i] << ", p = " << p[i];
        }
    }

    int scale = 10;
    vector<vector<int>> dp(w.size(),vector<int>(carry/scale + 1, 0));
    vector<vector<vector<bool>>> take_table(w.size(),vector<vector<bool>>(carry/scale + 1, vector<bool>(w.size(), false)));
    if(print) {
        cout << "\n dp row =" << dp.size() << ", dp col = " << dp[0].size();
    }

    for(int i = 1; i < dp.size(); i++) {
        for(int j = w_main_min/scale; j < dp[0].size(); j++) {
            int now_carry = j * scale;

            if(now_carry < w[i]) {//东西装不下，肯定不拿
                dp[i][j] = dp[i-1][j];
            } else {

                int get_thing_val, rest_carry, get, no_get;
                get_thing_val = w[i] * v[i];
                rest_carry    = j - w[i]/scale;
                get           = get_thing_val + dp[i-1][rest_carry];

                //no get
                no_get        = dp[i-1][j];

                if(p[i] == 0) {

                    if(get > no_get) {
                        take_table[i][j] = take_table[i-1][rest_carry];
                        take_table[i][j][i] = true;
                    }
                    dp[i][j] = std::max(get,no_get);

                } else if (p[i] > 0 && take_table[i-1][j][p[i]]) {

                    if(get > no_get) {
                        auto temp = take_table[i][j];
                        take_table[i][j] = take_table[i-1][rest_carry];

                        if(take_table[i][j][p[i]]) {
                            take_table[i][j][i] = true;
                            dp[i][j] = get;
                        } else {
                            take_table[i][j] = temp;
                            dp[i][j] = no_get;

                        }
                    }
                } else if(p[i] > 0 && !take_table[i-1][j][p[i]]) {
                    dp[i][j] = dp[i-1][j];
                }
            }

        }
    }

    if(print)  {
        for(int i = 1; i < dp.size(); i++) {
            cout << "\n row " << i << ": ";
            for(int j = w_main_min/scale; j < dp[0].size(); j++) {
                cout <<  dp[i][j] << ",";
            }
        }

        for(int i = 1; i < take_table.size(); i++) {
            cout << "\n row " << i << ": ";
            for(int j = w_main_min/scale; j < take_table[0].size(); j++) {

                for(int k = 0; k < 4; k++) {
                    cout <<  take_table[i][j][k] << ",";
                }

                cout << "    ";
            }
        }


    }

    cout << dp[dp.size()-1][dp[0].size()-1];

}