#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void main()
{
    int id=0;
    id = getpid();
    printf("id is %d\r\n",id);
}

