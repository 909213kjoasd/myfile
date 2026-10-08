#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

//声明可不写形参名
int check_pram(int, const char*, int);
int block_cur(const char*, int);
int process_create(const char*, const char*, int, int);
void process_wait(void);
