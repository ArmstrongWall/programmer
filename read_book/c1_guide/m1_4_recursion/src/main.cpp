#include <iostream>
void printDigit(int n)
{
    std::cout << n;
    
    return;
}

void printOut(int n)
{
    if(n/10)
        printOut(n/10);
    printDigit(n%10);
    return;
}

int main(int argc,char** argv)
{
    int a =76345;
    printOut(a);
   
    return 0;
}

