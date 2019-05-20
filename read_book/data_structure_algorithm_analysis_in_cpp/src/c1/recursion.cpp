//
// Created by johnny on 1/10/18.
//
#include <iostream>
#include <vector>
using namespace std;

void range()
{

    vector<int> ran = {1,2,3,5};

    std::cout << ran.size()<< endl;

    for(auto x : ran)
    {
        ++x;
        std::cout << x<< endl;
    }
}

void printDigit(int n)
{
    std::cout << n;

}

void printOut(int n)
{
    if(n/10)
        printOut(n/10);
    printDigit(n%10);

}

int recursion(int argc,char** argv)
{
    int a =76345;
    printOut(a);

    return 0;
}
