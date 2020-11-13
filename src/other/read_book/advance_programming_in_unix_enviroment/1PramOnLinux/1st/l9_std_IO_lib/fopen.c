#include<stdio.h>
void main()
{
    FILE *fp;
    char c_buf[15];

    fp = fopen("./test.txt","r+");
    
    fread(c_buf,1,10,fp);

    printf("now we read %s\n",c_buf);

    fclose(fp);
}
