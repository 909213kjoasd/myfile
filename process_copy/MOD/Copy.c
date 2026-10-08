#include<stdio.h>	
#include<unistd.h>	
#include<stdlib.h>	
#include<string.h>	
#include<sys/types.h>	
#include<sys/stat.h>	
#include<sys/fcntl.h>

int main(int argc, char** argv)
{
	int sfd;//源文件的文件描述符
	int	dfd;//目标文件的文件描述符
	int	offset = atoi(argv[3]);//rgv[3]是命令行第4个参数，代表偏移量offset，从第offset字节位置开始复制。	
i	int blocksize = atoi(argv[4]);//命令行第5个参数，每次read读取的字节大小

	if((sfd = open(argv[1],O_RDONLY))==-1) perror("open srcfile， failed");
	if((dfd = open(argv[2],O_WRONLY|O_CREAT,0664))==-1) perror("open srcfile, failed");

	lseek(sfd,offset,SEEK_SET);//SEEK_SET文件开头，读写指针移动到从文件开头往后offset字节处
	lseek(dfd,offset,SEEK_SET);

	char buffer[blocksize];//定义字符数组缓冲区，用来存放read读到的数据。
	int len;//保存read的返回值
	printf("child pid %d execl Copy, offset %d, blocksize,%d\n",getpid(),offset,blocksize);
	//通过len返回值判定是否读取完毕，可能循环读取
	len = read(sfd,buffer,sizeof(buffer));
	write(dfd,buffer,len);
	//传len，而不是sizeof(buffer)是因为文件末尾的时候，剩下的数据不足一块。
	//比如 buffer大小100，只剩30字节，read 返回len=30。防止残留旧脏数据一并写入文件，造成垃圾内容。

	close(sfd);
	close(dfd);
	return	0;
}
