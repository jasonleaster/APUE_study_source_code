#include<apue.h>
#include<fcntl.h>
#include<stdio.h>
int main()
{
	int file_descriptor = 0;
	int copy_file_descriptor = 0;
	int file_flags = 0;
	int ownership = 0;
	int temp = 0;

	if((file_descriptor = open("./text.t",O_RDWR)) < 0)
	{
		printf("open error\nProcess end\n");
		return 0;
	}

	printf("file_descriptor is %d\n",file_descriptor);

	//cmd = F_DUPFD ,dupliacte the file descriptor
	if((copy_file_descriptor = fcntl(file_descriptor,F_DUPFD,0)) < 0)
	{
		printf("fcntl error\nProcess end");
		return 0;
	}
	else
	{
		printf("The return value is %d\n",copy_file_descriptor);
	}
	
	//cmd = F_GETFD, return file descriptor flass for fiedes as the vale of the fucntion
	if(temp = fcntl(file_descriptor,F_GETFD) < 0)
	{
		printf("fcntl error\nProcess end\n");
		return 0;
	}
	else
	{
		printf("file descriptor is %d\n",temp);
	}
	
	//cmd = F_GETFL,return file status flags for filedes.
	if(file_flags = fcntl(file_descriptor,F_GETFL) < 0)
	{
		printf("fcntl error\nProcess end\n");
		return 0;
	}
	else
	{
		switch(file_flags& O_ACCMODE) //& O_ACCMODE)
		{
			case O_RDWR  :
				printf("file flags is O_RDWR\n");
				break;
			case O_RDONLY:
				printf("file flags is O_RDONLY\n");
				break;
			case O_WRONLY:
				printf("file flags is O_WRONLY\n");
				break;
		}

	   	if(file_flags&O_APPEND)
		{
			printf("file flags is O_APPEND\n");
		}	
		if(file_flags&O_NONBLOCK)
		{
			printf("file flags is O_NONBLOCK\n");
		}
		
		#if defined(O_SYNC)
		if(file_flags&O_SYNC)
		{	
			printf("file flags is O_SYNC\n");
		}
		#endif
	
		#if defined(O_DSYNC)
		if(file_flags&O_DSYNC)
		{
			printf("file flags is O_DSYNC\n");
		}
		#endif
		
		#if defined(O_FSYNC)
		if(file_descriptor&O_FSYNC) 
		{
			printf("file flags is O_FSYNC\n");
		}
		#endif
		
		#if defined(O_ASYNC)
		if(file_descriptor& O_ASYNC)
		{
			printf("file flags is O_ASYNC\n");
		}		
		#endif
	
		#if defined (O_RSYNC)
		if(file_descriptor&O_RSYNC)
		{
			printf("file flags is O_RSYNC\n");
		}
		#endif
	}
	
	//cmd = F_GETOWN
	if(ownership = fcntl(file_descriptor,F_GETOWN) < 0)
	{
		printf("fcntl error!\nProcess end\n");
		return 0;
	}
	else
	{
		printf("file ownership is %d",ownership);
	}

	return 0;
}
