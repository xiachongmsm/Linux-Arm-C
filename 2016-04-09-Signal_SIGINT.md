# Linux系统中的信号处理函数
* `category`:`信号处理`
* `tags`:`Linux` `C` `Signal`<br>
## Signal_SIGINT
    本程序是Linux系统中对于系统内核产生信号的基本处理方法。
    实现的功能是通过函数接收键盘按下“Ctrl+C”时产生的SIGINT信号。
    流程：
    1.声明信号处理函数handle_sig并注册
    2.休眠20s，如果始终没有按下“Ctrl+C”，程序正常退出
    3.如果在20s以内按下“Ctrl+C”，则进入函数handle_sig，输出“Ctrl + C is down.”，并退出

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void handle_sig(int num);

int main()
{
  //...............注册信号处理函数handle_sig，用于捕捉SIGINT信号......................//
  //SIGINT会在ctrl+c被按下是产生，当产生此信号时，调用回调函数handle_sig进行处理，使程序正常退出。
  signal(SIGINT,handle_sig);
  sleep(20);
  printf("In 20s, Nothing input, I am going to have a rest\n");
  return(0);
}

static void handle_sig(int num)
{
	printf("\nCtrl + C is down. \n");
	exit(1);
}
```
