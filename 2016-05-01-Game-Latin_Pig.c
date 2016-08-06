//拉丁猪游戏：输入一个单词，如：banana，找到其第一个元音字母，将其转化为 anana-bay
//示例：shine - ine-shay
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
void main()
{
	char str[512] = {0};
	int i = 0;
	int length = 0;
	int first_pos = 0;
	int aeiou_flag = 0;
	char str_after[512] = {0};
	char str_tem[512] = {0};
	while(1)
	{
		memset(str,0,sizeof(str));
		printf("Please input a word.\n");
		gets(str);
		length = strlen(str);
		if(length >0 )
		{
			i=0;
			if(str[i] =='a' ||str[i] =='e' ||str[i] =='i' ||str[i] =='o' ||str[i] =='u'||
				   str[i] =='A' ||str[i] =='E' ||str[i] =='I' ||str[i] =='O' ||str[i] =='U')
			{
				printf("first letter is vowel: %c\n",str[i]);
				continue;
			}
			for(i=1;i<length;i++)
			{
				if(str[i] =='a' ||str[i] =='e' ||str[i] =='i' ||str[i] =='o' ||str[i] =='u'||
				   str[i] =='A' ||str[i] =='E' ||str[i] =='I' ||str[i] =='O' ||str[i] =='U')
				{
					aeiou_flag = 1;
					first_pos = i;
					break;
				}
			}
			if(aeiou_flag == 1)
			{
				sprintf(str_tem,"%s",str+i);
				strcat(str_after,str_tem);
				char* temp =(char*)malloc(sizeof(char*));
				if(temp == NULL)
				{
					printf("malloc temp error\n");
					exit(0);
				}
				//memset(str_tem,0,sizeof(str_tem));
				memcpy(temp,str,first_pos);
				sprintf(str_tem,"-%say",temp);
				strcat(str_after,str_tem);
				printf("Latin_Pig:%s\n",str_after);
				free(temp);
				temp = NULL;
				break;
			}
			else
			{
				printf("Input words: %s\nNo vowel (aeiou)\n",str);
			}
		}
		else
		{
			printf("No item Input, try again.\n");
			continue;
		}
	}
}
