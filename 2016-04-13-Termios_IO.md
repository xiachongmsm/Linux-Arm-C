    /********************* Termios_IO ***************************
    title:Linux系统中的串口收发
    category:串口
    tags:Linux C Termios
    本程序是Linux系统中串口首发的基本框架。
    实现的功能是通过串口接收数据并将接收到的数据发回。
    流程：
    1.打开串口，在打开之前，需要对想要控制的串口，在终端中键入：sudo chmod 777 /dev/ttyS0
    2.将串口配置的结构体与描述符绑定，并进行工作模式设置，处理未写入的数据并激活串口。
    3.串口收发都使用接收集进行控制。
    */

    #include   <stdio.h>
    #include   <stdlib.h>
    #include   <unistd.h>
    #include   <fcntl.h>
    #include   <termios.h>  //串口头文件
    #include   <errno.h>
    #include   <string.h>
    #include   <math.h>
    static const char *dev1 = "/dev/ttyS0";
    static unsigned int uBaudRate[7] = {B2400, B4800, B9600, B19200, B38400, B57600, B115200};//波特率配置，压力传感器为9600

    int main()
    {
      int fd;
      struct termios term_in;
      if((fd = open(dev1, O_RDWR | O_NOCTTY))<0)
    	{
        printf("open dev1 error\n");
        return -1;
    	}
      if(tcgetattr(fd, &term_in))
      {
        exit(-1);
      }

      //..................		输入输出设置				...................//
    	term_in.c_iflag |= IGNPAR ;//输入设置；IGNPAR：忽略奇偶校验错误的字符

      term_in.c_oflag &= ~OPOST;//输出模式；不设置OPOST，使得所有其他标志都被忽略
      term_in.c_cflag &= ~CSIZE;

    	//控制模式：
    	term_in.c_cflag |= CS8;	            //设置数据位：8比特
    	term_in.c_cflag |= (CREAD | CLOCAL);//激活选项CREAD和CLOCAL，用于本地连接和接收使用。CREAD：启用接收字符器；CLOCAL：本地连接

    	//本地模式；ICANON：启用标准输入处理；ECHO：启用输入字符的本地回显功能；ECHOE：接收到ERASE时执行退格、空格、退格的动作组合。ISIG：启用信号。
    	term_in.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    	//..........			设置最小字符数和等待时间			..........//
    		//VMIN和VTIME值主要与read功能相关，如果VMIN＝0，VTIME＝0，read总是立即返回；
    		//如果VMIN>0，VTIME＝0，read在等待到VMIN个字符之后返回，返回值为读取的字符数量，到达文件末尾返回0；
    		//如果VMIN＝0，VTIME>0，当有字符可以处理或者经过VTime/10秒后返回；
    		//如果VMIN>0，VTIME>0，当read每接到一个字符，会启动一个定时器，在时间超过VTime/10秒后返回
    	term_in.c_cc[VTIME] = 1;	//TIME值
    	term_in.c_cc[VMIN] = 200;		//MIN值

    	//..........			设置波特率			..........//

    	cfsetospeed(&term_in, uBaudRate[3]);
    	cfsetispeed(&term_in, uBaudRate[3]);

    	//..........			处理未写入的数据			..........//
    	//tcflush：清空终端未完成的输入/输出请求及数据。TCIOFLUSH:清除正写入的数据，且不会发送至终端。
    	tcflush(fd, TCIOFLUSH);

    	//..........			激活配置			..........//
      //tcsetattr函数:激活配置。配置完成之后需要激活配置使其生效。TCSANOW：不等数据传输完毕就立即改变属性。
    	if(tcsetattr(fd, TCSANOW, &term_in) != 0)
    	{
    		printf("set pressure termios err\n");                                                     //配置压力串口出错
    	}
      char temp_read[1024] = {0};
      fd_set rfds,sfds;
      int ret;
      while(1)
    	{
    		memset(temp_read,0,sizeof(temp_read));
    		FD_ZERO(&rfds);// 清空串口接收端口集
    		FD_SET(fd,&rfds);// 设置串口接收端口集
    		ret = select(fd+1,&rfds,NULL,NULL,NULL);
    		if(ret == -1)
      	{
        	perror("select()");
        	continue;
      	}
    		if(FD_ISSET(fd,& rfds))
    		{
    			ret = read(fd, temp_read, sizeof(temp_read));	//将串口接收端的数据读取到temp_read中
          printf("%s\n", temp_read);
        }
        FD_ZERO(&sfds);// 清空串口接收端口集
        FD_SET(fd,&sfds);// 设置串口接收端口集
        ret = select(fd+1,NULL,&sfds,NULL,NULL);
        if(ret == -1)
        {
          perror("select()");
          continue;
        }
        if(FD_ISSET(fd,& sfds))
        {
          write(fd, temp_read, strlen(temp_read));//将接收到的信息通过串口发回
        }
      }
    }
