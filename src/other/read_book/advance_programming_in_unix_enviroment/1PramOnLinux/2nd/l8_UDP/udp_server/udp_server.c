/*                                                                                                                              
 *创建日期：2017.5.28
  功能：UDP服务器
  作者：JohnnyWang
  log： 2017.5.28 实现接收客户端数据
 *
 * */

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>//使用struct sockaddr_in需包含的头文件
#include <arpa/inet.h>//使用inet_ntoa网络地址转换成字符串函数需包含的头文件 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define portnum 8888//自定义网络端口
#define MSG_SIZE 128

int main()
{
    int sockfd;//定义文件描述符,新的客户机文件描述符
    struct sockaddr_in server_addr;//主机地址属性
    struct sockaddr_in client_addr;//客户机地址
    char buffer[MSG_SIZE];//接收数据缓存
    int nbyte;
    int addrlen;

    //创建套接字
    //socket函数的两个参数一个是确定套接字通信域 
    //AF_INET  ipv4通信域 
    //AF_INET6 ipv6通信域
    //第二个是套接字类型
    //SOCK_DGRAM  长度固定，无连接的不可靠的报文传递 UDP
    //SOCK_RAW    IP协议的数据报接口
    //SOCK_STREAM 有序、可靠、双向字节流  TCP
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) == -1)//如果创建错误，就返回
    {
        printf("create socket error\r\n");
        exit(1);
    }
    //设置要绑定的地址
    bzero(&server_addr,sizeof(struct sockaddr_in));//将地址结构体先清零
    server_addr.sin_family = AF_INET;       //网络域
    server_addr.sin_port   = htons(portnum);//将两个字节的端口转换成网络字节序
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//将任意的IP地址赋予数据段

    //绑定地址
    bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr));
    //第二个参数一般先使用sockaddr_in（便于定义结构体成员变量），然后在强制转化，能够更方便
    
    
    while(1)
    {
        addrlen = sizeof(struct sockaddr);
        bzero(buffer,sizeof(buffer)); 
        //接收数据
        nbyte = recvfrom(sockfd,buffer,MSG_SIZE,0,(struct sockaddr*)(&client_addr),&addrlen);
        buffer[nbyte] = '\0';
        
        printf("server recv : %s\r\n",buffer);//打印接收的数据

    }

    close(sockfd);

}
