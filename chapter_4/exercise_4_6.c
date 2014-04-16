/*****************************************************************
code writer :liuzijian

data : 2014.01.07

file name :exercise_4_6.c

code purpose:

	This code for program named as "cp_like".Use could use this 

program like "cp_like ./file1 ./file2 ./file3 ...".file1 will be copyed to 

file2 file3 etc.Extraodinary,"file1" muse be a file  that containing a 

holes for the exercise 6 asked.
******************************************************************/
#include"stdio.h"
#include"apue.h"
#include"fcntl.h"
#include"stdlib.h"
#define BUFFSIZE 4096
int main(int argc,char* argv[])
{
	int temp = 0;
	int* fds = NULL;
	ssize_t num = 0;
 
	char buf[BUFFSIZE];	
	
	fds = malloc((argc-2)*sizeof(int)) ;
	
	if(fds == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(0);
	}

	if((fds[0] = open(argv[1],O_RDWR)) < 0)
	{
		printf("%s open error!\n",argv[1]);
		exit(0);
	}

	for(temp = 2;temp<argc;temp++ )
	{
		if(fds[temp-1] = open(argv[temp],\
O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH) < 0)
		{
			printf("%s open error!\n",argv[temp]);
			exit(0);
		}
		
		printf("fds%d",fds[temp-1]);
		while(num = read(fds[0],buf,BUFFSIZE-1) >  0)
		{
			if(write(fds[temp-1],buf,BUFFSIZE-1) != num)
			{
				printf("write error");
				exit(0);
			}	
		}
		
		if(num < 0)
		{
			printf("read error!\n");
		}
		
	}
	
	free(fds);
	exit(0);
}
