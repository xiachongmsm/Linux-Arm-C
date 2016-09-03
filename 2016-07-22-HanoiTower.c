/*
使用递归实现汉诺塔，输入汉诺塔的盘子数，A为初始塔，C为目标塔，B为借助塔
*/
#include <stdio.h>
int i = 1;
void move(int n, char start, char end);
void hanoi(int n,char start, char path, char end);
int main()
{
  int N;
  printf("请输入盘子的数量\n");
  scanf("%d",&N);
  char a = 'A',b = 'B',c = 'C';
  hanoi(N,a,b,c);
  return 0;
}

void hanoi(int n,char start, char path, char end)
{
  if(n == 1)
  {
    move(n,start,end);
  }
  else
  {
    hanoi(n-1,start,end,path);
    move(n,start,end);
    hanoi(n-1,path,start,end);
  }
}

void move(int n, char start, char end)
{
  printf("第%d步，将盘子%d由%c移动 -> %c . \n",i,n,start,end );
  i++;
}
