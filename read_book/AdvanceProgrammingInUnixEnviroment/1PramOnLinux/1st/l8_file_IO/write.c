#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void main()
{
    int fd;
    char *buf = "987654321";
    char buf1[10];
    fd = open("/home/wzq/linux_pram/l8_file_IO/test1.c",O_RDWR
            |O_CREAT,0755);
    //mode:0755 
    if(fd < 0)
        printf("open file file failes!\n");

   write(fd,buf,7);

    //buf[5] = "\0";//添加字符串结束符

    read(fd,5,buf1);

    printf("buf1 is %s\n",buf1);

    close(fd);
}
