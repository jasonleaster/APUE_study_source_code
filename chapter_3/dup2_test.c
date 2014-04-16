#include<apue.h>
#include"fcntl.h"
#include<stdio.h>
int main()
{
	int file_descriptor;
	if((file_descriptor = open("./text.t",O_RDWR)) < 0)
	{
		printf("error\n");
	}
	else
	{
		printf("file descriptor is %d\n",file_descriptor);
	}

	printf("dup2 return value:%d\n dup return value\
 %d\n",dup2(file_descriptor,1),dup(file_descriptor));

	printf("dup2 return value:%d\ndup return value\
 %d\n",dup2(file_descriptor,10),dup(file_descriptor));

	printf("dup2 return value:%d\ndup return value\
 %d\n",dup2(file_descriptor,11),dup(file_descriptor));

	close(file_descriptor);
	return 0;
}
