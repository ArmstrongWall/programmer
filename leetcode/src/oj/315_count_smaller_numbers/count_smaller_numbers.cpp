//
// Created by johnny on 6/29/19.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <ctime>

#include "count_smaller_numbers.h"

class Solution {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {


        std::vector<std::pair<int,int>> nums_pair;
        std::vector<int>                count;

        for (int i = 0; i < nums.size(); i++) {
            std::pair<int,int> a {nums[i],i};
            nums_pair.push_back(a);
            count.push_back(0);
        }


        mergesort_devide(nums_pair,count);

        return count;

    }




    void mergesort_devide(std::vector<std::pair<int,int>>& nums_pair,std::vector<int>& count) {

        if (nums_pair.size() <= 1) {
            return;
        }

        std::vector<std::pair<int,int>> sub_vec_1;
        std::vector<std::pair<int,int>> sub_vec_2;

        int mid = nums_pair.size() / 2;

        for (int i = 0; i < mid; i++) {
            sub_vec_1.push_back(nums_pair[i]);
        }

        for (int i = mid; i < nums_pair.size(); i++) {
            sub_vec_2.push_back(nums_pair[i]);
        }

        mergesort_devide(sub_vec_1,count);
        mergesort_devide(sub_vec_2,count);

        mergesort_deal(sub_vec_1, sub_vec_2, nums_pair, count);
    }



    void mergesort_deal(std::vector<std::pair<int,int>>& pair_vec_1,
                        std::vector<std::pair<int,int>>& pair_vec_2,
                        std::vector<std::pair<int,int>>& vec,
                        std::vector<int>& count) {


        vec.clear();


        int i = 0;
        int j = 0;


        while (i < pair_vec_1.size() && j < pair_vec_2.size()) {
            if(pair_vec_1[i].first <= pair_vec_2[j].first) {
                vec.push_back(pair_vec_1[i]);
                count[pair_vec_1[i].second] += j;
                i++;
            } else {
                vec.push_back(pair_vec_2[j]);
                j++;
            }
        }

        for(;i < pair_vec_1.size(); i++) {
            vec.push_back(pair_vec_1[i]);
            count[pair_vec_1[i].second] += j;// 7777 1111
        }

        for(;j < pair_vec_2.size(); j++) {
            vec.push_back(pair_vec_2[j]);//1111 7777
        }

    }

    void mergesort_two_vec(std::vector<int>& sub_vec_1,
                           std::vector<int>& sub_vec_2,
                           std::vector<int>& vec_) {
        int i = 0;
        int j = 0;

        vec_.clear();

        while (i < sub_vec_1.size() && j < sub_vec_2.size()) {
            if(sub_vec_1[i] <= sub_vec_2[j]) {
                vec_.push_back(sub_vec_1[i]);
                i++;
            } else {
                vec_.push_back(sub_vec_2[j]);
                j++;
            }
        }
        for(;i < sub_vec_1.size(); i++) {
            vec_.push_back(sub_vec_1[i]);
        }
        for(;j < sub_vec_2.size(); j++) {
            vec_.push_back(sub_vec_2[j]);
        }
    }

    void mergesort_recurive(std::vector<int>& vec) {

        if (vec.size() <= 1) {
            return;
        }

        std::vector<int> sub_vec_1;
        std::vector<int> sub_vec_2;

        int mid = vec.size() / 2;

        for (int i = 0; i < mid; i++) {
            sub_vec_1.push_back(vec[i]);
        }

        for (int i = mid; i < vec.size(); i++) {
            sub_vec_2.push_back(vec[i]);
        }

        mergesort_recurive(sub_vec_1);
        mergesort_recurive(sub_vec_2);

        mergesort_two_vec(sub_vec_1, sub_vec_2, vec);
    }

};

int count_smaller() {
    Solution s;
    std::vector<int> a = {1,3,6,8};
    std::vector<int> b = {2,4,7,9};
    std::vector<int> result;

    s.mergesort_two_vec(a,b,result);

    for(auto &x : result) {
        std::cout << x <<",";
    }

    std::cout << "mergesort_recurive\n";

    Solution s1;
    std::vector<int> a1 = {1,3,6,8,45,3,22,6,44,77};

    s1.mergesort_recurive(a1);

    for(auto &x : a1) {
        std::cout << x <<",";
    }
    std::cout << "\nmergesort_recurive big data test\n";
    std::vector<int> v1;
    std::vector<int> v2;
    srand(time(NULL));
    for(int i = 0; i < 10000; i++) {
        int num = (rand()*rand())%100003;
        v1.push_back(num);
        v2.push_back(num);
    }
    s1.mergesort_recurive(v1);
    std::sort(v2.begin(),v2.end());

    assert(v1.size() == v2.size());

    for(int i = 0; i < v1.size(); i++) {
        assert(v1[i] == v2[i]);
    }
    std::cout << "\ntest finish,success\n";


    std::cout << "\ntest countSmaller\n";
    Solution s2;
    std::vector<int> c = {5,2,6,1,0,0,4};
    std::vector<int> d ;
    d = s2.countSmaller(c);

    for(auto &x : d) {
        std::cout << x <<",";
    }



    return 0;
}