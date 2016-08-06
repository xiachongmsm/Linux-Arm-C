/********************* System_Getdate ***************************
title:Linux系统中的当前日期&时间的获取
category:系统
tags:Linux C date
本程序是用于Linux系统中时间的获取和装订输出
实现的功能是将ctime结构体中的日期和时间的对应项进行格式化处理。
流程：
1.使用time()和ctime()函数得到的日期的格式为Tue Oct 13 07:24:04 2015
2.将日期格式调整成为2015,10,13,07:24:04.000 或2015,10,13,072404.000
*/
#include <stdio.h>
#include <time.h>
#include <string.h>
void get_month(char Month[]);
void get_date(char Date[]);
void main()
{
 char date[32] = {0};
 get_date(date);
 printf("after convert:   %s\n",date);
}

//该函数用于将月份由英文字母缩写转化为数字
void get_month(char Month[])
{
 char mon1[4] = "Jan";
 char mon2[4] = "Feb";
 char mon3[4] = "Mar";
 char mon4[4] = "Apr";
 char mon5[4] = "May";
 char mon6[4] = "Jun";
 char mon7[4] = "Jul";
 char mon8[4] = "Aug";
 char mon9[4] = "Sep";
 char mon10[4] = "Oct";
 char mon11[4] = "Nov";
 char mon12[4] = "Dec";
 char num1[] = "01";
 char num2[] = "02";
 char num3[] = "03";
 char num4[] = "04";
 char num5[] = "05";
 char num6[] = "06";
 char num7[] = "07";
 char num8[] = "08";
 char num9[] = "09";
 char num10[] = "10";
 char num11[] = "11";
 char num12[] = "12";
 if(strncmp(Month,mon1,3)==0)
   strcpy(Month,num1);
 else if(strncmp(Month,mon2,3)==0)
   strcpy(Month,num2);
 else if(strncmp(Month,mon3,3)==0)
   strcpy(Month,num3);
 else if(strncmp(Month,mon4,3)==0)
   strcpy(Month,num4);
 else if(strncmp(Month,mon5,3)==0)
   strcpy(Month,num5);
 else if(strncmp(Month,mon6,3)==0)
   strcpy(Month,num6);
 else if(strncmp(Month,mon7,3)==0)
   strcpy(Month,num7);
 else if(strncmp(Month,mon8,3)==0)
   strcpy(Month,num8);
 else if(strncmp(Month,mon9,3)==0)
   strcpy(Month,num9);
 else if(strncmp(Month,mon10,3)==0)
   strcpy(Month,num10);
 else if(strncmp(Month,mon11,3)==0)
   strcpy(Month,num11);
 else if(strncmp(Month,mon12,3)==0)
   strcpy(Month,num12);
 else
   printf("month is error:%s",Month);
}

void get_date(char Date[])
{
 char date_buf[32] = {0};
 time_t ti;
 time(&ti);   /*获得系统时间，存放在结构体ti中*/
 sprintf(date_buf,"%s",ctime(&ti));/*ctime把日期和时间转换为字符串，并格式化输出到缓存中*/
 printf("before convert:  %s\n",date_buf);
 char year[8] = {0};
 char month[4] = {0};
 char day[4] = {0};
 char hour[4] = {0};
 char minu[4] = {0};
 char sec[8] = {0};
 strncat(year,date_buf+20,4);
 //printf("year = %s\n",year);
 strncat(month,date_buf+4,3);
 get_month(month);
 //printf("month = %s\n",month);
 strncat(day,date_buf+8,2);
 //printf("day = %s\n",day);
 strncat(hour,date_buf+11,2);
 //printf("hour = %s\n",hour);
 strncat(minu,date_buf+14,2);
 //printf("minu = %s\n",minu);
 strncat(sec,date_buf+17,2);
 //printf("sec = %s\n",sec);
 //两种不同格式的输出通过下边的这句语句进行调整。
 sprintf(Date,"%.4s,%.2s,%.2s,%.2s:%.2s:%.2s.000", year, month,day,hour,minu,sec);
 //sprintf(Date,"%.4s,%.2s,%.2s,%.2s%.2s%.2s.000", year, month,day,hour,minu,sec);

}
