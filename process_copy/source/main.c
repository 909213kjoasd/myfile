#include <process_copy.h>
int main(int argc,char ** argv)
{
	int pronum; 
	int blocksize; 
	if(argv[3]==0) pronum=3;//不传第4个参数，默认是3个子进程
	else pronum = atoi(argv[3]);//有第4个参数，转成数字
	check_pram(argc, argv[1], pronum);//检查参数数量是否合法、源文件能不能打开
	blocksize = block_cur(argv[1], pronum);//切片，算出每一块有多大
	process_create(argv[1], argv[2], pronum, blocksize);//创建子进程
 	return 0;
}
