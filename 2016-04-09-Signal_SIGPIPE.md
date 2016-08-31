# Linux系统中的信号处理函数-Signal_SIGPIPE
* `category`:`信号处理`
* `tags`:`Linux` `C` `Signal` `Socket`

>本程序是Linux系统中对于系统内核产生信号SIGPIPE的处理方法。<br>
基于TCP协议的Socket连接建立后，若某一端关闭连接，而另一端仍然向它写数据。<br>
第一次写数据后会收到RST响应，此后再写数据，内核将向进程发出SIGPIPE信号，通知进程此连接已经断开。<br>
而SIGPIPE信号的默认处理是终止程序。<br>
为避免此情况发生，可以使用类似“2016-04-09-Signal_SIGINT.md”提到的，使用注册信号处理函数来处理。<br>
此情况下，直接使用语句“signal(SIGPIPE, SIG_IGN)”即可。<br>
也可以使用本文中的方法，通过使用信号屏蔽集的方法进行处理。<br>
>>流程：
1.清空信号掩码集 sigset<br>
2.将 SIGPIPE 信号放入信号集 sigset 中<br>
3.将信号集含有SIGPIPE的信号集sigset屏蔽<br>

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int main()
{
  int err;
  sigset_t sigset;					//定义一个信号集sigset

	err = sigemptyset(&sigset);                           	//清空信号掩码集 sigset
	if(err == -1)
	{
		printf("sigemptyset err!\n");
		exit(-1);
	}
	err = sigaddset(&sigset, SIGPIPE);		     	//将 SIGPIPE 信号放入信号集 sigset 中
	if(err == -1)
	{
		printf("sigaddset err!\n");
		exit(-1);
	}
	err = sigprocmask(SIG_SETMASK, &sigset, NULL);       	//将 sigset 和NULL 合并，并设置为屏蔽字
	if(err == -1)
	{
		printf("sigprocmask err!\n");
		exit(-1);
	}
}
```
