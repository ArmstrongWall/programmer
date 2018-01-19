#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void main()
{
    int fd,fd1;
    char *buf = "987654321";
    char buf1[10];
    fd = open("/home/wzq/linux_pram/l8_file_IO/test1.c",O_RDWR
            |O_CREAT,0755);
    //mode:0755 
    if(fd < 0)
        printf("open file file failes!\n");

   write(fd,buf,7);//把buf的字符串写入test1.c中

   fd1=dup(fd);
    //buf[5] = "\0";//添加字符串结束符
    lseek(fd1,0,SEEK_SET);

    read(fd1,buf1,5);
   //参数二和参数三的顺序不要搞错 

    printf("buf1 is %s\n",buf1);

    close(fd1);
}
