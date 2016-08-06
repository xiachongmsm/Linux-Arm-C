//根据文件大小，从文件中读取字符并统计其中的单词数量
//使用fseek()+ftell()+malloc可以读取一个任意大小的文件
//判断单词的思想：存在非空格和非换行认为单词开始，开始之后，遇到空格/换行/文件结束时认为单词结束。
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
void main()
{
	FILE *fp = NULL;
	char file_name[] = "test.txt";
	int fsize = 0;
	fp = fopen(file_name,"r+");
	if(fp== NULL)
	{
		perror("open file eror");
		exit(0);
	}
	else
	{
		fseek(fp,0,SEEK_END);
		fsize = ftell(fp);
		rewind(fp);
		char *str = (char *)malloc(fsize*sizeof(char));
		if(str == NULL)
		{
			printf("malloc error\n");
			exit(0);
		}
		else
		{
			fread(str,1,fsize,fp);
			printf("%s\n",str);
			fclose(fp);
		}
		int length = 0;
		int num_word = 0;
		//length = strlen(str);
		length = fsize;
		//printf("%d\n",length);
		if(length == 0)
		{
			printf("Nothing in file.%d word\n",num_word);
		}
		else if(length == 1)
		{
			if(str[0] !=' ' && str[0] != '\n')
			{
				num_word = 1;
				printf("%d word(s) in file.\n",num_word);
			}
		}
		else
		{
			int i;
			int start_flag = 0;
			int end_flag = 0;
			for(i=0;i<length;i++)
			{
				if(start_flag == 0 && str[i]!=' ' && str[i] != '\n')
				{
					start_flag = 1;
				}
				if(start_flag == 1 &&( str[i] ==' ' || str[i] == '\n' || (i==length-1)))
				{
					end_flag = 1;
				}
				if(start_flag ==1 && end_flag == 1)
				{
					num_word+=1;
					start_flag = 0;
					end_flag = 0;
				}
			}
			printf("%d word(s) in file.\n",num_word);
		}
	free(str);
	str = NULL;
	}
}
