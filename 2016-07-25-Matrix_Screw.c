#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
void Fun(int n, int ** a);
int main()
{
  int n,i,j;
  printf("请输入螺旋矩阵的维数：\n");
  scanf("%d",&n);

  //根据实际的输入大小进行内存分配
  int **point = (int **)malloc(n*sizeof(int *));
  if(point == NULL)
  {
    printf("malloc point error\n");
    return 1;
  }
  for(i=0;i<n;i++)
  {
    *(point+i) = (int *)malloc(n*sizeof(int));
    if(NULL == *(point+i))
    {
      printf("malloc *(point+%d) error\n",i );
      return 1;
    }
    for(j=0;j<n;j++)
    {
      *(*(point+i)+j) = 0;
    }
  }

  //对N×N的方阵进行螺旋赋值，打印输出，并释放分配的指针
  Fun(n,point);
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      printf("%4d", *(*(point+i)+j));
    }
    printf("\n");
    free(*(point+i));
  }
  free(point);
}

void Fun(int n, int ** a)
{
  int i,j,m=1;
  for(i=0;i<n/2;i++)
  {
    for(j=i;j<n-i;j++)
    {
      if(a[i][j] == 0)
      {
        //printf("1,%d\n",m);//上三角内的点
        a[i][j] = m++;
      }
    }
    for(j=i+1;j<n-i;j++)
    {
      if(a[j][n-1-i] == 0)
      {
        //printf("2,%d\n",m);//右侧三角内的点
        a[j][n-1-i] = m++;
      }
    }
    for(j=n-1-i;j>i;j--)
    {
      if(a[n-1-i][j] == 0)
      {
        //printf("3,%d\n",m);//下三角内的点
        a[n-1-i][j] = m++;
      }
    }
    for(j=n-1-i;j>i;j--)
    {
      if(a[j][i] == 0)
      {
        //printf("4,%d\n",m);//左侧三角内的点
        a[j][i] = m++;
      }
    }
    if(n%2 == 1)
    {
      //printf("5,%d\n",m);//奇数维矩阵时的中心点
      a[n/2][n/2] = m;
    }
  }
}
