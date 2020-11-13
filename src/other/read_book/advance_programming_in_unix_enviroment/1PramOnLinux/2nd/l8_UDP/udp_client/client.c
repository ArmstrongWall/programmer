/*
 *创建日期：2017.5.20
  功能：UDP传输客户端
  作者：JohnnyWang
  log： 2017.5.29 实现向服务器发送文件
* */
 
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>//定义了sockaddr_in结构
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#define portnum     8888//自定义网络端口
#define BUFFER_SIZE 128
 
int main(int argc, char **argv)
{
    FILE * stream;    //定义流去文件
    int sockfd,new_fd;//定义文件描述符,新的客户机文件描述符
    struct sockaddr_in server_addr;//主机地址属性
    char buffer[BUFFER_SIZE]; //发送数据缓存
    int nbyte,i=0;
 
    if(argc !=2)
    {
        printf("Usage: %s server_ip\n",argv[0]);
        exit(-1);
    }
                                                                                                                                             
    //创建套接字
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) == -1)//如果创建错误，就返回
    {
        printf("create socket error\r\n");
        exit(1);
    }
    //设置要绑定的地址
    bzero(&server_addr,sizeof(struct sockaddr_in));//将地址结构体先清零
    server_addr.sin_family = AF_INET; //网络域                                                                                
    server_addr.sin_port   = htons(portnum);//将两个字节的端口转换成网络字节序
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//将任意的IP地址
    inet_aton(argv[1],&server_addr.sin_addr);
 
 
        //发送数据到服务器
    while(1)//不断读取文件
    {
        printf("Please input char:\r\n");
        fgets(buffer,BUFFER_SIZE,stdin);
         
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr));
        bzero(buffer,BUFFER_SIZE);
        //printf("send some data..\r\n");
 
    }
 
    printf("传输数据结束.....\r\n");
 
    //4.关闭连接
    close(sockfd);
 
    return 0;
 
}

