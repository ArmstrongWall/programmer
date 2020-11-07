//
// Created by Johnny on 2019/8/4.
//

#include <vector>
#include <iostream>
#include <map>
#include "hash.h"

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x),next(nullptr) {}
};

int hashkey_func(int key, int table_len) {
    return key % table_len;
}

void hash_table_insert(int table_len, ListNode * node, ListNode * hash_map[]) {
    int hash_key        = hashkey_func(node->val,table_len);
    node->next          = hash_map[hash_key];
    hash_map[hash_key]  = node;
}

bool search(ListNode *hash_table[], int value, int table_len){
    int hash_key = hashkey_func(value, table_len);
    ListNode *head = hash_table[hash_key];
    while(head){
        if (head->val == value){
            return true;
        }
        head = head->next;
    }
    return false;
}

int hash() {

    int TABLE_LENGTH = 11;
    ListNode * hash_map[TABLE_LENGTH] = {nullptr};
    std::vector<ListNode*> listnode;
    int test[8] = {1,1,4,9,20,30,150,1500};
    for(auto &x : test) {
        listnode.push_back(new ListNode(x));
    }

    for(auto &x : listnode) {
        hash_table_insert(TABLE_LENGTH,x,hash_map);
    }

    std::cout << "Hash table is : \n" ;

    for(int i = 0; i < TABLE_LENGTH; i++) {
        printf("[%d]",i);
        ListNode* head = hash_map[i];
        while (head) {
            printf("->%d",head->val);
            head = head->next;
        }
        std::cout << "\n" ;
    }


    printf("Test search:\n");
    for (int i = 0; i < 10; i++){
        if (search(hash_map, i, TABLE_LENGTH)){
            printf("%d is in the hash table.\n",i);
        }
        else{
            printf("%d is not in the hash table.\n",i);
        }
    }

    std::map<std::string, int> hash_map1;
    std::string str1 = "abc";
    std::string str2 = "aaa";
    std::string str3 = "xxxxx";
    hash_map1[str1] = 1;
    hash_map1[str2] = 2;
    hash_map1[str3] = 100;
    if (hash_map1.find(str1) != hash_map1.end()){
        printf("%s is in hash_map1, value is %d\n",
               str1.c_str(), hash_map1[str1]);
    }
    std::map<std::string, int> ::iterator it;
    for (it = hash_map1.begin(); it != hash_map1.end(); it++){
        printf("hash_map1[%s] = %d\n", it->first.c_str(), it->second);
    }

    return 0;

}