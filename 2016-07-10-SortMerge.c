/*
归并排序
即将两个都升序（或降序）排列的数据序列合并成一个仍按原序排列的序列。
例程：有一个含有6个数据的升序序列和一个含有4个数据的升序序列，将二者合并成一个含有10个数据的升序序列。
*/
#include <stdio.h>
#define m 6
#define n 4
int main()

{
  int a[m]={-3,6,19,26,68,100} ,b[n]={8,10,12,22};
  int i,j,k,c[m+n];
  i=j=k=0;
  while(i<m && j<n)
  {
    if(a[i]<b[j])
    {
      c[k]=a[i];
      i++;
    }
    else
    {
      c[k]=b[j];
      j++;
    }
    k++;
  }
  while(i>=m && j<n)
  {
    c[k]=b[j];
    k++;
    j++;
  }
  while(j>=n && i<m)
  {
    c[k]=a[i];
    k++;
    i++;
  }

  for(i=0;i<m+n;i++)
    printf("%d  ",c[i]);
  printf("\n" );
  return 0;
}
