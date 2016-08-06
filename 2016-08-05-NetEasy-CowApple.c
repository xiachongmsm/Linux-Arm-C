/*
2017年网易内推测试题
一共有n只奶牛，每只奶牛有Ni个苹果。
尝试将苹果在奶牛之间互相交换，每一次只能将2个苹果，从一个奶牛处移动到另一个奶牛处。
如果可以平均分配，输出需要移动的最小次数。
如果不能移动，输出-1。
输入示例
3
2 4 6
输出示例
1
输入示例
3
1 2 3
输出示例
-1
*/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
int main()
{
	int cow_num,apple_num;
	scanf("%d",&cow_num);
	int *apple = NULL;
	apple = (int*)malloc(cow_num*sizeof(int));
	int i = 0;
	apple_num = 0;
	for(i=0;i<cow_num;i++)
	{
		scanf("%d",&apple[i]);
		apple_num+=apple[i];
		//printf("%d\n",apple[i]);
	}
	if(apple_num%cow_num != 0)//总苹果数不能被奶牛数整除，返回-1
	{
		printf("%d",-1);
		free(apple);
		return(-1);
	}
	else
	{
		int ave = 0;
		int time = 0;
		int time_tmp = 0;
		ave = apple_num/cow_num;
		for(i=0;i<cow_num;i++)
		{
			if(abs(apple[i] - ave) %2 !=0)	//Ni-苹果平均数不能被2整除，返回-1
			{
				printf("%d",-1);
				free(apple);
				return(-1);
			}
			else
			{
				if(apple[i] > ave)
				{
					time_tmp = (apple[i] - ave)/2;
					time += time_tmp;
				}
			}
		}
		printf("%d",time);
		free(apple);
	}
	return(0);
}
