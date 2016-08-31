# UDP协议下的典型服务器(接收非阻塞)和客户端
* `category`:`网络编程`
* `tags`:`Linux` `C` `socket`

## server
		本程序是UDP协议服务器的最简单框架。
		实现的功能是接收客户机发来的信息并把收到信息发回客户端，并打印出来。
		流程：
		1.利用socket（）函数创立一个UDP协议套接字
		2.初始化协议地址结构（包括协议族，本地地址，端口号）
		3.利用bind（）函数绑定套接字与服务器地址
		4.将套接字设置为非阻塞
		5.进入死循环while（1），在循环中先是将缓存清零，再读取客户机发来的信息，之后将信息发送回客户端。
		6.当收到“close”时，关闭套接字，服务器自动停止。

```C
#include<stdio.h>
#include <errno.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>	//...用于设置套接字为非阻塞...//
int main()
{
	int client_len;
	int fd,rs,err;
	char buf[1024];
	/*** 建立一个基于UDP协议的网络套节字 ***/
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd<0)
	{
		perror("socket is error");
		exit(1);
	}
	/*** 设置服务器IP地址和端口号并与套接字绑定 ***/
	struct sockaddr_in server,client;
	client_len=sizeof(struct sockaddr_in);
	memset(&server,0,sizeof(struct sockaddr_in));
	server.sin_family=AF_INET;
	server.sin_port=htons(12345);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	int optval = 1;
	setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(optval));
	err=bind(fd,(struct sockaddr *)&server,sizeof(struct sockaddr_in));
	if(err<0)
	{
		perror("bind is error");
		exit(1);
	}
	//...设置套接字为非阻塞...//
	int net_flags;
	net_flags = fcntl(fd,F_GETFL);
	net_flags = O_NONBLOCK;
	if(fcntl(fd,F_SETFL,net_flags)==-1)
	{
		perror("fail to fcntl");
		return(-1);
	}
	/*** UDP协议不基于连接，不用listen，直接可以使用recvfrom和sendto进行收发 ***/
	while(1)
	{
	 	bzero(buf,sizeof(buf));//每次都将缓存部分清零，保证数据不被上一次干扰
	 	rs=recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr *)&client,&client_len);
		if(rs == -1 && errno != EAGAIN)
		{
			perror("fail to receive\n");
			return(-1);
		}
		else if(errno == EAGAIN && rs == -1)
		{
				printf("Nothing recv\n" );
				sleep(1);
				continue;

		}
		else
		{
			sendto(fd,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(struct sockaddr_in));
		 	printf("server receive:%s\n",buf);
		 	if(strcmp(buf,"close") == 0)
		 	{
		 		break;
		 	}
		}
	}
	close(fd);
	return(0);
}
```

## client
* `category`:`网络编程`
* `tags`:`Linux` `C` `socket`

		本程序是UDP协议客户机的最简单框架.
		实现的功能是发送“close”给服务器，然后从服务器接受服务器返回的信息并打印出来。
		流程：
		1. 利用socket（）函数创建套接字
		2.初始化协议地址结构（包括协议族，本地地址，端口号）
		3.给服务器发送“close”，并接受服务器返回信息“close”。
		4.关闭套接字。
		
```C
#include<stdio.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int addr_len;
	char buffer[1024];
	struct sockaddr_in addr;
	int fd,err;
	char buf[]="close";

	/*** 建立一个基于UDP协议的网络套节字 ***/
	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd<0)
	{
		perror("socket error");
		exit(1);
	}
	/*** 设置服务器IP地址和端口号并与套接字绑定 ***/
	addr_len = sizeof(struct sockaddr_in);
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(12345);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	while(1)
	{
		err=sendto(fd,buf,sizeof(buf),0,(struct sockaddr *)&addr,sizeof(struct sockaddr_in));
		if(err <0)
		{
			perror("sendto error");
			exit(1);
		}
		err=recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&addr_len);
		if(err <0)
		{
			perror("recvfrom error");
			exit(1);
		}
		printf("client receive:%s\n",buffer);
		if(strcmp(buf,buffer) == 0)
	 	{
	 		break;
	 	}
	}
	close(fd);
	return 0;
}
```
