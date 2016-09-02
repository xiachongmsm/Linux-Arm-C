/*
  有序序列的插入排序算法，就是将某数据插入到一个有序序列后，该序列仍然有序。
  例程：任意读入10个整数，将其用插入法按降序排列后输出。
  输入示例：3 1 2 5 6 4 8 9 7 0
  输出示例额：9   8   7   6   5   4   3   2   1   0
*/
#include <stdio.h>
#define n 10
int main()
{
  int a[n],i,j,k,x;

  scanf("%d",&a[0]);

  for(j=1;j<n;j++)
  {
    scanf("%d",&x);
    if(x<a[j-1])
      a[j]=x;
    else
    {
      i=0;
      while(x<a[i]&&i<=j-1)
        i++;
      for(k=j-1;k>=i;k--)
        a[k+1]=a[k];
      a[i]=x;
    }
  }
  for(i=0;i<n;i++)
    printf("%4d",a[i]);
  printf("\n");
  return 0;
}
