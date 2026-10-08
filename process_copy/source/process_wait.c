#include<process_copy.h>

void process_wait()
{
	pid_t zpid;
	while((zpid=wait(NULL))>0)//wait (NULL)：Linux系统调用。
		                      //父进程阻塞，直到有一个子进程结束，该函数让内核回收子进程，返回这个退出子进程的pid
							  //所有子进程全部回收完毕，wait返回-1，不再阻塞。
	{
		printf("Parent wait child success,zpid %d\n",zpid);
	}
}
