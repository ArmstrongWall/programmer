#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char **argv)
{
    int fd_s,fd_t;
    int count = 0;
    char buf[512];

    //1.打开源文件
    fd_s = open(argv[1],O_RDONLY);

    //2.打开目标文件
    fd_t = open(argv[2],O_RDWR|O_CREAT,0666);

    //3.读取源文件数据
while((count = read(fd_s,buf,512))>0)
        {
             //4.将读取的数据写入目标文件
            write(fd_t,buf,count);
        }
    //5.关闭文件
    close(fd_t);
    close(fd_s);
}
