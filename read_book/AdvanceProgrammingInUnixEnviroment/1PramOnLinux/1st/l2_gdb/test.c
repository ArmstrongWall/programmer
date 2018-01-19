#include <stdio.h>
void myprint(int res)
{
    printf("res is %d\n",res);
}

void main()
{
    int i=0;

    int result =0;

    for(i=0;i<100;i++)
    {
        result =0;
    }

    myprint(result);
}
