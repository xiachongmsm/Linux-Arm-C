/*
实现内部开始的螺旋矩阵的输出：
中心点的坐标为（0,0）
坐标点的值由所在圈数，朝向和坐标值三者决定
21   22   23   24   25
20    7    8    9   10
19    6    1    2   11
18    5    4    3   12
17   16   15   14   13

*/
#include <stdio.h>
#define Max(a,b) ((a)>(b)?(a):(b))
#define Abs(a)   (a>0)?(a):(-a)
int func(int a, int b);
int main()
{
  int x,y;
  int N;
  printf("请输入旋转矩阵的维数：\n" );
  scanf("%d",&N);
  for(y=-N;y<=N;y++)
  {
    for(x=-N;x<=N;x++)
    {
      printf("%5d",func(x,y));
    }
    printf("\n");
  }
  return 0;
}

int func(int a, int b)
{
  int t = Max(Abs(a),Abs(b));//坐标点(a,b)所在的圈数
  int v = (t+t-1) * (t+t-1);
  if(a == -t)
  {
    v += 5*t - b;
  }
  else if (b == -t)
  {
    v += 7*t + a;
  }
  else if(b == t)
  {
    v += 3*t-a;
  }
  else
  {
    v += t + b;
  }
  return v;
}
