//冒泡排序的实现
#include<stdio.h>
#include<stdlib.h>
#define N 8
void Sort_Bubble(int a[],int n);
//冒泡排序的一般实现
void Sort_Bubble(int a[],int n)//n为数组a的元素个数
{
  //一定进行N-1轮比较
  for(int i=0; i<n-1; i++)
  {
    //每一轮比较前n-1-i个，即已排序好的最后i个不用比较
    for(int j=0; j<n-1-i; j++)
    {
      if(a[j] > a[j+1])
      {
        int temp = a[j];
        a[j] = a[j+1];
        a[j+1]=temp;
      }
    }
  }
}
//冒泡排序的优化实现，可在已排好序后提前跳出循环
void Sort_Bubble_better(int a[],int n)//n为数组a的元素个数
{
  //最多进行N-1轮比较
  for(int i=0; i<n-1; i++)
  {
    char isSorted = 1;
    //每一轮比较前n-1-i个，即已排序好的最后i个不用比较
    for(int j=0; j<n-1-i; j++)
    {
      if(a[j] > a[j+1])
      {
        isSorted = 0;
        int temp = a[j];
        a[j] = a[j+1];
        a[j+1]=temp;
      }
    }
    if(isSorted) break; //如果没有发生交换，说明数组已经排序好了
  }
}
int  main()
{
  int num[N] = {89, 38, 11, 78, 96, 44, 19, 25};
  Sort_Bubble(num, N); //或者使用Sort_Bubble_better(num, N);
  for(int i=0; i<N; i++)
    printf("%d  ", num[i]);
  printf("\n");
  return 0;
}
