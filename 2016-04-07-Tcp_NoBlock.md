		/*********************             说明                  ***************************
		title:典型TCP协议下的Tcp服务器(接收非阻塞)和客户端的
		category:网络编程
		tags:Linux C

		/*********************             server                  ***************************
		本程序是tcp协议服务器的最简单框架。实现的功能是接收客户机发来的信息并把收到信息打印出来，每次打印出来之后把“I am server”字符串发给客户机。
		流程：
		1.利用socket（）函数创立一个tcp协议套接字
		2.初始化协议地址结构（包括协议族，本地地址，端口号）
		3.利用bind（）函数绑定套接字与服务器地址
		4.利用listen（）函数开始进行监听是否有客户机的连接申请
		5.设置keepalive 心跳包检测的参数并激活
		6.使用accept（）函数获得客户机的信息（地址，端口号）
		6.进入死循环while（1），在循环中先是将缓存清零，再读取客户机发来的信息，判断是否读取结束，之后再将接收到的消息返回给客户机。
		7.如此循环，直到客户机关闭套接字，服务器自动停止。
		*/
		#include <netdb.h>
		#include <sys/socket.h>
		#include <errno.h>
		#include <netinet/in.h>
		#include <sys/types.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <sys/mman.h>
		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <pthread.h>
		#include <netinet/tcp.h>
		#include <signal.h>
		#include <fcntl.h>	//...用于设置套接字为非阻塞...//
		#include <math.h>
		# define MAXLEN 1024
		int main()
		{
			int socket_fd, new_fd;						//网络套节字和连接套节字
			struct sockaddr_in server_addr, client_addr;		//socket结构体，存储服务器和客户端的相关信息
			int portnumber;				 			//端口号
			int err;							//记录返回的错误信息
			int r;							//记录接收的返回值
			int r_s;							//记录发射的返回值
			int net_connect_flag;					//网络连接状态的标志位
			char buff_IP_addr[32];						//客户端IP地址的缓存
			socklen_t len;							//记录client_addr的长度
			char recv_buffer[MAXLEN] = {0};
			//.............keepAlive 变量初始化...............................//
			int keepAlive = 1; 						// 开启keepalive属性
			int keepIdle = 10; 						// 如该连接在10秒内没有任何数据往来,则进行探测
			int keepInterval = 5; 						// 探测时发包的时间间隔为5秒
			int keepCount = 3; 						// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.

			portnumber = 9999;						//接收命令端口号9999
			len = sizeof(client_addr);					//记录client_addr的长度

			/*** 建立一个基于TCP协议的网络套节字 ***/
			if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)		//创建一个网络套接字标准程序
			{
				return(-1);
			}

			/*** 设置服务器IP地址和端口号 ***/
			memset(&server_addr, 0, sizeof(struct sockaddr_in));	//清空服务器结构体
			server_addr.sin_family = AF_INET;			//根据服务器的情况为套接字命名的标准程序，设置为IPv4
			server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			server_addr.sin_port = htons(portnumber);		//设置端口号

			/*** 将IP地址和端口号绑定到套节字上 ***/
			if(bind(socket_fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)	//将服务器结构题和该套节字绑定
			{
				return(-1);
			}

			/*** 监听本地端口 ***/
			if(listen(socket_fd, 1) == -1)				//创建一个队列，等待连接的标准程序 listen(socket_fd, 1)
			{
				return(-1);
			}

			 //..............激活keepalive........................//
			if(setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive)) != 0)
			{
				perror("Set keepalive error");
			}

			if(setsockopt(socket_fd, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle)) != 0)
			{
				perror("Set keepIdle error");
			}
			if(setsockopt(socket_fd, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval)) != 0)
			{
				perror("Set keepInterval error");
			}
			if(setsockopt(socket_fd, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount)) != 0)
			{
				perror("Set keepCount error");
			}
			//..................receive/resolve command part....................//
			while(1)
			{
				/***  	等待客户端连接 	***/
				printf("TCP receive: before accept,wait to be connected !\n");
				if((new_fd = accept(socket_fd, (struct sockaddr *)(&client_addr), &len)) == -1)	//接受一个连接的标准程序 ，程序会在此阻塞，等待有客户端的connect命令到来，与其相连。
				{
					perror("accept err!\n");
					break;
				}
				net_connect_flag = 1;		//成功连接，网口连接状态标志位，置1
				inet_ntop(AF_INET,&client_addr.sin_addr,buff_IP_addr,sizeof(buff_IP_addr));	//将IP地址由2进制转化为字符，以用于显示
				printf("receive:accept success,connection from %s,port %d \n",buff_IP_addr,ntohs(client_addr.sin_port));	//ntohs(client_addr.sin_port)可将客户端的端口号转化为int		
				while(1)
				{

					//.....接收命令和检包 ...............................//            
					memset(recv_buffer, 0, MAXLEN);	//命令包故缓存清零
					r = recv(new_fd, recv_buffer, MAXLEN, MSG_DONTWAIT);	//接收来自上述客户端的数据，MSG_DONTWAIT设置为非阻塞模式

					if(r < 0)
					{
						if(errno==ECONNRESET)//表示连接被复位了，已经无效了，关闭它，删除它
						{
							perror("ECONNRESET");	//连接重置，跳出循环，等待重新accept
							break;
						}
						else if(errno==ETIMEDOUT)
						{
							perror("ETIMEDOUT");	//网线断开，跳出循环，等待重新accept
							net_connect_flag = 0;
							break;
					 	}
					 	else
					 	{
					    		continue;//其他错误，如没有数据往下传送
					 	}     	
					}
					else if(r == 0)			//客户端关闭socket_fd,如断开连接，返回0，跳出循环，等待重新accept
					{
						printf("The client is closed!\n");
						net_connect_flag = 0;
						break;
					}
					else					//接收到正确的数据
					{					
						printf("recv_buffer = %s,r = %d \n",recv_buffer,r);
						r_s = send(new_fd, recv_buffer, r, 0);//将接收到的内容发送回客户端
						if(r_s < 0)
						{
							close(new_fd);
							break;
						}
					}
				}
				close(new_fd);

			}
		}






		/**********************             client                  ***************************
		本程序是tcp协议客户机的最简单框架，实现的功能是发送“I am client”给服务器，然后从服务器接受服务器返回的信息并打印出来。发送和接收过程会实现两次。
		流程：
		1. 利用socket（）函数创建套接字
		2.初始化协议地址结构（包括协议族，本地地址，端口号）
		3.利用connect（）函数 与服务器建立连接
		4.循环两次给服务器发送“I am client”，并接受服务器返回信息。
		5.关闭套接字，断开与服务器的连接。
		*/
		#include<stdio.h>
		#include<sys/types.h>
		#include<arpa/inet.h>
		#include<unistd.h>
		#include<stdlib.h>
		#include<string.h>
		#include<errno.h>
		#include<unistd.h>
		#include<sys/socket.h>
		#include<netinet/in.h>
		int main()
		{
			int socket_fd;
			int err;
			int send_num,recv_num;
			char send_buffer[]="I am client";
			char recv_buffer[256] = {0};
			struct sockaddr_in server;
			socket_fd=socket(AF_INET,SOCK_STREAM,0);//创建套接字
			if(socket_fd<0)
			{
				printf("socket error\n");

			}
			memset(&server,0,sizeof(server));
			server.sin_family=AF_INET;//初始化协议地址结构
			server.sin_port=htons(9999);
			server.sin_addr.s_addr=htonl(INADDR_ANY);
			err=connect(socket_fd,(struct sockaddr *)&server,sizeof(struct sockaddr));//连接服务器
			if(err==0)
			{
				printf("client connect succeed!\n");
			}
			else
			{
				perror("connect error");
				exit(1);
			}
			while(1)
			{
				send_num=send(socket_fd,send_buffer,sizeof(send_buffer),0);//给服务器发送信息
				printf("send success: %s\n",send_buffer);
				recv_num=recv(socket_fd,recv_buffer,sizeof(recv_buffer),0);//从服务器接受信息
				if(recv_num<0)
				{
					perror("recv error");
				}
				else
				{
					//recv_buffer[recv_num]='\0';
					printf("recv success: %s\n",recv_buffer);
					break;
				}
			}
			printf("ending connection\n");
			close(socket_fd);//关闭套接字，断开连接
			return(0);
		}
