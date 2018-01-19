#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void main()
{
    int fd;
    fd = open("/home/wzq/linux_pram/l8_file_IO/test1.c",O_RDWR
            |O_CREAT,0755);
    //mode:0755 
    if(fd < 0)
        printf("open file file failes!\n");

    close(fd);
}
