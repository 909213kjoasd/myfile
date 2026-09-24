#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/mman.h>
#include<regex.h>

 int main()
 {
     //1.准备正则表达式
     char* regstr="<a[^>]\\+\\?href=\"\\([^\"]\\+\\?\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>";

     //2.准备正则结构体
     regex_t reg;
     regcomp(&reg, regstr, 0);

     //3.把数据源映射到内存中
     int fd;
     fd = open("url.html", O_RDWR);//读写模式
     int size;
     size = lseek(fd, 0, SEEK_END);

     char* mmap_data = NULL;
     mmap_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
     close(fd);


     //4.遍历查找
     int regnum = 3;
     regmatch_t match[regnum];
     char link[1024];
     char title[1024];
     while (regexec(&reg, mmap_data, regnum, match, 0) == 0)
		 //参数：&reg编译好的正则；mmap_data：待匹配字符串；regnum分组数量；match保存结果；0是flag
         //返回值==0：匹配成功，进入循环；匹配失败返回非0，退出while
     {
         //提取数据
         bzero(link, sizeof(link));//bzero：把link数组全部置0（清空，相当于初始化\0）
         bzero(title, sizeof(title));
         snprintf(link, match[1].rm_eo - match[1].rm_so + 1, "%s", mmap_data + match[1].rm_so);
         snprintf(title, match[2].rm_eo - match[2].rm_so + 1, "%s", mmap_data + match[2].rm_so);
         mmap_data += match[0].rm_eo;
         printf("匹配结果：title=%s, link=%s\n", title, link);
     }
	 regfree(&reg);         // 释放正则占用的内存
     munmap(mmap_data, size);// 解除文件内存映射
     return 0;
 }
