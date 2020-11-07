//
// Created by Johnny on 2020/11/7.
//
#include <vector>
#include <string>
#include <list>
#include <map>
#include <iostream>
#include "listToTree.h"

/*输入例子1:

[["d1", "d0", "IT"], ["d2", "d0", "RD"], ["d0", "", "The Company"], ["d3", "d0", "HR"]]


输出例子1:

["The Company","HR","IT","RD"]


例子说明1:

On each level of the department tree, departments are listed in alphabetical order of the name*/

class Solution {
public:
    /**
     * Convert the department list to preorder traversal of the department tree
     * @param departments string字符串二维数组 [["id1", "parentId", "name"]...], there's only one root department with empty parent id.
     * @param departmentsRowLen int departments数组行数
     * @param departmentsColLen int* departments数组列数
     * @return string字符串vector
     */
    struct Node {
        std::string value;
        std::list<Node*> children;
        explicit Node(const std::string &v): value(v) {}
        void push_children(Node* one_child) {

            if(children.empty()) {
                children.push_back(one_child);
            } else if(children.front()->value[0] < one_child->value[0]) {
                children.push_back(one_child);
            } else if(children.front()->value[0] >= one_child->value[0]) {
                children.push_front(one_child);
            }
        }
    };

    void print(const Node* node, std::vector<std::string>& result) {
        std::cout << node->value << ",";
        result.push_back(node->value);
        if(!node->children.empty()) {
            for(auto child : node->children) {
                print(child,result);
            }
        }
    }
    std::vector<std::string> listToTree(std::vector<std::vector<std::string>> departments, int departmentsRowLen, int departmentsColLen) {
        // write code here
        std::string  root_key;
        std::map<std::string, Node*> table;
        for(int i = 0; i < departmentsRowLen; i++) {
            Node* node      = new Node(departments[i][2]);
            std::string key = departments[i][0];
            table[key]      = node;
            if(departments[i][1].empty()) {
                root_key = departments[i][0];
            }
        }

        for(int i = 0; i < departmentsRowLen; i++) {
            if(!departments[i][1].empty()) {
                table[departments[i][1]]->push_children(table[departments[i][0]]);
            }
        }

        std::vector<std::string> result;
        print(table[root_key],result);
        return result;

    }
};


int listToTree() {

    std::vector<std::vector<std::string>> s = {{"d1", "d0", "IT"},{ "d2", "d0", "RD"}, {"d0", "", "The Company"}, {"d3", "d0", "HR"}};
    Solution sl;
    sl.listToTree(s,4,3);

    std::vector<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);


    std::vector<int> temlist;

    std::cout <<  "keeeeeeeee";
    temlist.assign(list.begin() + 2, list.begin() + 3);

    for(int i = 0; i < temlist.size(); i++) {
        std::cout << temlist[i] << ",";
    }

    return 0;
}















