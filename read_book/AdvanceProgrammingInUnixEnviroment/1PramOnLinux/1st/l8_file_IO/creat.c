#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
    int fd;
    fd = creat("/home/wzq/linux_pram/l8_file_IO/test2.c",0621);
    //mode:0755 
    if(fd < 0)
        printf("creat file file failes!\n");
}
