#include<stdio.h>
void main()
{
    FILE *fp;
    char *c_buf = "9876565";

    fp = fopen("./test.txt","r+");
   
    fseek(fp,8,SEEK_SET);

    fwrite(c_buf,5,1,fp);


    fclose(fp);
}
