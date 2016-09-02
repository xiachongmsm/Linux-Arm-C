/*
二分法查找的思路是：要查找的关键值同数组的中间一个元素比较，若相同则查找成功，结束；
否则判别关键值落在数组的哪半部分，就在这半部分中按上述方法继续比较，直到找到或数组中没有这样的元素值为止。

例程：任意读入一个整数x，在升序数组a中查找是否有与x等值的元素。
*/
#include <stdio.h>
#define n 10
int main()
{
  int a[n]={2,4,7,9,12,25,36,50,77,90};
  int x,high,low,mid;
  scanf("%d",&x);
  high=n-1;
  low=0;
  mid=(high+low)/2;
  while(a[mid]!=x&&low<high)
  {
    if(x<a[mid])
      high=mid-1;
    else
      low=mid+1;
    mid=(high+low)/2;
  }
  if(x==a[mid])
    printf("Found %d at a[%d]\n",x,mid);
  else
    printf("Not found\n");
}
