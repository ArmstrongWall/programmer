#include <iostream>
using namespace std;  

template <typename T>
int compare(const T &v1, const T &v2)
{
    if(v1 > v2)
        return 1;
    else
        return 0;
}

int main()
{
    cout << compare(1,0) << endl;
    return 0;

}
