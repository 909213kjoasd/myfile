#include<process_copy.h>
int	process_create(const char * srcfile, const char	* destfile, int	pronum,	int blocksize)	
{
	char offset_str[50];//字符数组，用来把数字offset转成字符串，execl要求参数必须是字符串
	char blocksize_str[50];//把数字blocksize转成字符串

	pid_t pid; 
	int i;
	for(i=0;i<pronum;i++)//创建子进程
	{
		pid =fork(); 
		if(pid == 0) break;
	}

	if(pid > 0)//父进程，调回收函数（循环回收所有子进程）
	{
	process_wait();
	}
	
	else if(pid == 0)
	{	
	int	offset;	
	offset =i * blocksize;//计算当前子进程负责的偏移量
	sprintf(offset_str,	"%d", offset);//数字转字符串，存入offset_str	
	sprintf(blocksize_str, "%d", blocksize);////数字转字符串，存入blocksize_str
	execl("/home/zxy777/five/Process/process_copy/MOD/Copy", "Copy",
	srcfile, destfile, offset_str, blocksize_str,NULL);//execl 是可变参数函数，必须用NULL标记参数结束,否则报错
	perror("execl failed"); //只有execl失败才会打印这句话
	//子进程execl之前的代码会正常执行，execl 执行成功就会替换整个进程映像，原有后续代码直接被覆盖、不再运行；只有execl调用失败时，才会执行execl后面的错误处理代码，用来打印报错并退出子进程。
	}
	
	else
	{
	printf("fork called error");
	}
	
	return 0;
}
