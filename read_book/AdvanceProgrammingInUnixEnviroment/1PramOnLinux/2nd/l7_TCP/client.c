#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>//定义了sockaddr_in结构
#include <string.h>
#include <stdio.h>

#define portnum 3333//自定义网络端口
int main()
{
    int sockfd,new_fd;//定义文件描述符,新的客户机文件描述符
    struct sockaddr_in server_addr;//主机地址属性
    char buffer[128];//接收数据缓存
    int nbyte;

    //1.创建套接字
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1)//如果创建错误，就返回
    {
        printf("create socket error\r\n");
        exit(1);
    }

    //2.1 设置要连接的服务器的地址
    bzero(&server_addr,sizeof(struct sockaddr_in));//将地址结构体先清零
    server_addr.sin_family = AF_INET;       //网络域
    server_addr.sin_port   = htons(portnum);//将两个字节的端口转换成网络字节序
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.141");//服务器的地址


    //2.2连接服务器
    if((connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))) == -1)
    {
        printf("connect error\r\n");
        exit(1);
    }
    
    //3.发送数据到服务器
    printf("Please input char sent to server\r\n");
    fgets(buffer,128,stdin);
    send(sockfd,buffer,strlen(buffer),0);

    //4.关闭连接
    close(sockfd);

    return 0;

}
