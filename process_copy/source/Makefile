#Rource中的makfile负责代码的编译集成，生成 ELF执行文件

TARGET=process_copy
INCLUDE_PATH=../include/
LIBRARY_PATH=
#查找执行后缀文件
SRCFILE=$(wildcard *.c) #当前目录下所有后缀为.c的C源码
DESTFILE=$(patsubst %.c, %.o, $(SRCFILE)) #把SRCFILE里面所有xxx.c，批量替换成xxx.o
CFLAGS=-I$(INCLUDE_PATH) -g -Wall
CC=gcc


#自底向上执行命令（先编译，再链接），自顶向下建立依赖关系！！！


$(TARGET):$(DESTFILE)
	$(CC) $^ -o $@   #链接：把一堆.o合并成最终 ELF 可执行文件
	                 #这里拆成.c→.o→ELF 是为了只重新编译修改过的文件。

%.o:%.c
	$(CC) $(CFLAGS) -c $<  #自动编译修改过的.c生成.o
