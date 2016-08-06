/********************* Thread_cond ***************************
title:Linux系统中的多线程编程
category:多线程
tags:Linux C Thread
本程序是Linux系统中线程的创建以及条件变量和互斥所的使用。
实现的功能是创建两个线程，一个线程休眠，用另一个线程唤醒该线程。
流程：
1.建立两个线程，一个处于休眠状态(thrd_sleep)，另一个处于活跃状态(thrd_wakeup)
2.通过使用条件变量和互斥锁，定义wait_flag和wakeup_flag函数，在活跃线程中唤醒休眠线程
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <pthread.h>						///和线程相关的头文件

void wait_flag(int *flag);					   //线程等待函数
void wakeup_flag(int *flag);					 //线程唤醒函数
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
int thread_flag = 0;
int stop_flag = 0;
void *thrd_sleep(void* arg);
void *thrd_wakeup(void* arg);

int main()
{
  int err;
  pthread_t tid;
  err = pthread_create(&tid, NULL, thrd_sleep, NULL);
  if(err != 0)
  {
    printf("thrd_sleep pthread error.\n");
    exit(-1);
  }
  err = pthread_create(&tid, NULL, thrd_wakeup, NULL);
  if(err != 0)
  {
    printf("thrd_wakeup pthread error.\n");
    exit(-1);
  }
  while(1)
  {
    if(stop_flag == 1)
      break;
  }
  return(0);
}

void *thrd_sleep(void* arg)
{
  printf("Sleep: My work is to sleep\n");
  wait_flag(&thread_flag);
  printf("Sleep: It's time to wake up\n");
  stop_flag = 1;
}

void *thrd_wakeup(void* arg)
{
  char str[64] = {0};
  printf("Wakeup: If you want to wake up the other thread, input 'wakeup'\n");
  while(scanf("%s",str) != EOF)
  {
    if(strcmp(str,"wakeup") == 0)
    {
      printf("Wakeup: I will wake up the thread.\n");
      wakeup_flag(&thread_flag);
      break;
    }
    else
    {
      printf("If you want to wake up the other thread, input 'wake up'\n");
    }
  }
}

void wait_flag(int *flag)					//线程等待函数
{
	pthread_mutex_lock (&qlock);
	while(*flag == 0)
		pthread_cond_wait(&qready, &qlock);
	*flag = 0;
	pthread_mutex_unlock(&qlock);
}

void wakeup_flag(int *flag)					//线程唤醒函数
{
	pthread_mutex_lock(&qlock);
	*flag = 1;
	pthread_mutex_unlock(&qlock);
	pthread_cond_broadcast(&qready);
}
