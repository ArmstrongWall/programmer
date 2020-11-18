//
// Created by wzq on 2020/11/15.
//

#include "string_plus.h"
#include<iostream>
#include<string>

using namespace std;

int big_plus(void) {
    string addend,augend,res;


    while(cin>>addend>>augend) {

        res.clear();
        int base_length = std::max(addend.size() ,augend.size());
        for(int i = 1; i <= base_length; i++) {
            res.push_back('0');
        }

        int an    = addend.size() - augend.size();
        int count = an > 0 ? an : -an;
        for(int i = 0; i <= count; i++) {
            if(addend.size() > augend.size()) {
                augend.insert(0,"0");
            }else if(addend.size() < augend.size()) {
                addend.insert(0,"0");
            }
        }

        int overtake = 0;
        for(int i = res.size() - 1; i >= 0; i--) {

            int single_up   = addend[i] - '0';
            int single_down = augend[i] - '0';
            int sum = single_up + single_down + overtake;
            if(sum >= 10) {
                overtake = 1;
                sum-=10;

            }else {
                overtake = 0;
            }
            res[i] = '0' + sum;
        }
        if(overtake) {
            res = "1" + res;
        }

        cout  << res << endl;

    }


    return 0;

}