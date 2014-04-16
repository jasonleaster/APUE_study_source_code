#include "apue.h"
#include "fcntl.h"
#include "stdio.h"
#include "unistd.h"
#define BUFFSIZE 1024

int main()
{
	int file_descriptor = 0;
	char buffer[BUFFSIZE];
	
	if((file_descriptor = open("./test.txt",O_RDWR)) < 0)
	{
		printf("open error\n");
	}	
	
	memset(buffer,0,BUFFSIZE*sizeof(char));
	
	printf("before truncation\n");
	while(read(file_descriptor,buffer,BUFFSIZE-1) > 0)
	{
		if(write(STDIN_FILENO,buffer,BUFFSIZE-1) <=0)
		{
			printf("write error\n");
		}
	}
	
	ftruncate(file_descriptor,sizeof(char)*40);
	
	lseek(file_descriptor,0,SEEK_SET);

	memset(buffer,0,BUFFSIZE*sizeof(char));
	
	printf("after truncation\n");
	while(read(file_descriptor,buffer,BUFFSIZE-1) > 0)
	{
		if(write(STDIN_FILENO,buffer,BUFFSIZE-1) <=0)
		{
			printf("write error\n");
		}
	}
	
	close(file_descriptor);
	return 0;
}
