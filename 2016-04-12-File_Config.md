#Linux系统中对文件读写
* `category`:`文件操作`
* `tags`:`Linux` `C` `File`

    本程序是Linux系统中对于文件读写/修改等基本操作。
    实现的功能是检查系统中是否存在配置文件config.txt.如果存在，读取其中的内容并输出。
    如果不存在，新建config.txt并写入内容。
    流程：
    1.使用access()判断文件是否存在，如果不存在，新建文件config.txt，并写入内容"I am config.txt"。
    2.如果文件存在，使用fopen+fread+fclose函数实现文件的打开读取和关闭。
    3.使用fseek+ftell+rewind函数，通过得到文件的大小，读取文件的内容并输出。
    
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
int main()
{
  int err,fsize;
	char filename[] = "config.txt";
  char config[] = "I am config.txt";
  FILE *fpconfig = NULL;
  err = access(filename,F_OK);	//检查文件test.txt是否存在
	if(err == 0)     //文件存在
	{
		fpconfig = 	fopen(filename, "r");
    if(fpconfig == NULL)
  	{
  		err = errno;
  		if(err == 2)		//文件路径不存在时，errno的返回值为2.
  		{
  			printf("file not exist\n");
  			exit(-1);
  		}
  		if(err == 30)		//文件为只读时，errno的返回值为30.
  		{
        printf("file read only\n");
  			exit(-1);
  		}
  	}
    else
  	{
      fseek(fpconfig,0L,SEEK_END);  //文件指针移动至文件尾部
      fsize=ftell(fpconfig);        //得到文件位置指针当前位置相对于文件首的偏移字节数
      printf("file size = %d字节\n",fsize);
      rewind(fpconfig);
      char *str_file =NULL;
      str_file = (char*)malloc(fsize+1);
      if( str_file== NULL)
      {
        printf("malloc error\n");
        exit(0);
      }
      err = fread(str_file,fsize,1,fpconfig);
      if(err == -1)
  		{
  			perror("read config.txt' error: ");
        exit(0);
  		}
      printf("%s\n",str_file);
      free(str_file);
      err = fclose(fpconfig);
      if(err == -1)
  		{
  			perror("close config.txt' error: ");
        exit(0);
  		}
  		return 0;
  	}
	}
	else
	{
    fpconfig = 	fopen(filename, "w+");
		if(fpconfig == NULL)
		{
			perror("create config.txt error "); //打印错误信息
		}
    else
    {
      err = fwrite(config,strlen(config),1,fpconfig);
      if(err == -1)
  		{
  			perror("write config.txt' error: ");
        exit(1);
  		}
      err = fclose(fpconfig);
      if(err == -1)
  		{
  			perror("close config.txt' error: ");
  		}
  		return 0;
    }
	}
}
```
