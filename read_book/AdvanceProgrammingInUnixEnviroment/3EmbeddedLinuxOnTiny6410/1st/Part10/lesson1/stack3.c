#include <stdio.h>

void func2(int a,int b)
{
    int k;
    k=a+b;
}

void func1(int a,int b)
{
	int c;
	func2(3,4);
	c=a+b;
}

int main()
{
    func1(1,2);
    return 0;
}
