#include <iostream>
#include <vector>
using namespace std;

int main(int argc,char** argv)
{
    
    vector<int> ran = {1,2,3,5};

    std::cout << ran.size()<< endl;

    for(auto x : ran)
    {
        ++x;
        std::cout << x<< endl;
    }
}
