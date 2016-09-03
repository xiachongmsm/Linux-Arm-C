/*
实现一个N维的Zigzag矩阵，矩阵元素沿45度对角线递增
如：
0       1       5
2       4       6
3       7       8
*/
#include <stdio.h>
#define N 3
void main()
{
  int a[N][N];
  int i,j,k;
  int num = 0;
  a[0][0] = num;
  ++num;
  for(k=1;k<2*N-1;k++)
  {
    for(i=0;i<N;i++)
    {
      for(j=0;j<N;j++)
      {
        if(i+j == k && k%2 == 1)
        {
          a[i][j] = num;
          ++num;
          continue;
        }
        else if(i+j == k && k%2 == 0)
        {
          a[j][i] = num;
          ++num;
          continue;
        }
        else
          continue;
      }
    }
  }
  for(i=0;i<N;i++)
  {
    for(j=0;j<N;j++)
    {
      printf("%8d",a[i][j]);
    }
    printf("\n");
  }
}
