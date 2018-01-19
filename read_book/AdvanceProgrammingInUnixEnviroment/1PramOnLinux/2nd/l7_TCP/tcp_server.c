#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>//使用struct sockaddr_in需包含的头文件
#include <arpa/inet.h>//使用inet_ntoa网络地址转换成字符串函数需包含的头文件 
#include <string.h>
#include <stdio.h>

#define portnum 3333//自定义网络端口
int main()
{
    int sockfd,new_fd;//定义文件描述符,新的客户机文件描述符
    struct sockaddr_in server_addr;//主机地址属性
    struct sockaddr_in client_addr;//客户机地址
    char buffer[128];//接收数据缓存
    int nbyte;
    int sin_size;

    //1.创建套接字
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1)//如果创建错误，就返回
    {
        printf("create socket error\r\n");
        exit(1);
    }
    //2.1 设置要绑定的地址
    bzero(&server_addr,sizeof(struct sockaddr_in));//将地址结构体先清零
    server_addr.sin_family = AF_INET;       //网络域
    server_addr.sin_port   = htons(portnum);//将两个字节的端口转换成网络字节序
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//将任意的IP地址赋予数据段

    //2.2绑定地址
    bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr));
    //第二个参数一般先使用sockaddr_in（便于定义结构体成员变量），然后在强制转化，能够更方便
    
    //3.监听端口
    listen(sockfd,5);//最大连接数是5
    
    while(1)
    {
        //4.等待连接 
        sin_size = sizeof(struct sockaddr);
        new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size);//等待连接,注意第三个参数必须是指针
        printf("server get connection from %s\r\n",inet_ntoa(client_addr.sin_addr));//将客户机地址转化成字符串，打印客户机地址
    
        //5.接收数据
        nbyte = recv(new_fd,buffer,128,0);
        buffer[nbyte] = '\0';
        printf("server recv : %s\r\n",buffer);//打印接收的数据

        //6.结束连接
        close(new_fd);
        //break;
    }

    close(sockfd);

}
