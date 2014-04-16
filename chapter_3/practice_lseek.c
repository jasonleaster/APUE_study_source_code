/*
just a demo for lseek
*/
#include"apue.h"
#include"stdio.h"
#include"unistd.h"
#include"fcntl.h"

int main()
{
	off_t file_off_set = 0;
	int file_descriptor = 0;
	
	if((file_descriptor = open("./text.t",O_RDONLY)) < 0)
	{
		printf("open error\nProcess end\n");
		return 0;
	}
	
	if((file_off_set = lseek(file_descriptor,file_off_set,SEEK_CUR)) < 0)
	{
		printf("lseek error\n");
		return 0;
	}
	else
	{
		printf("lseek execute successful\nCurent file off-set is %d\n",file_off_set);
	}
	return 0;
}
