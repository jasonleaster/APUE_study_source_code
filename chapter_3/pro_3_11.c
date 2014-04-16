#include"myerr.h"
#include"apue.h"
#include"fcntl.h"
#include"stdio.h"
int main(int argc ,char *argv[])
{
	int val = 0;
	printf("argc is = :%d\nargv[1] = :%s \n",argc,argv[1]);

	if (argc != 2)
	{
		err_quit("usage: a.out <descriptor#>");
	}	
	
	printf("atoi(argv[1]) is  %d\n",atoi(argv[1]));
	if((val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
	{
		err_sys("fcntl error for fd %d",atoi(argv[1]));
	}
	printf("\nval is %d O_ACCMODE is %d\n",val,O_ACCMODE);
	printf("O_RDNOLY is %d\n",O_RDONLY);

	printf("O_WRONLY is %d\n",O_WRONLY);
	
	printf("O_RDWR is %d\n",O_RDWR);
	switch (val & O_ACCMODE)
	{
		case O_RDONLY :
		{
			printf("read only\n");
			break;
		}
		case O_WRONLY:
		{
			printf("write only\n");
			break;
		}
		case O_RDWR :
		{
			printf("read write\n");
			break;
		}
		
		default :
			err_dump("unknown access mode\n");
	}

	if (val & O_APPEND)
	{
		printf(",append");
	}
	if (val & O_NONBLOCK)
	{
		printf(",nonblocking");
	}
	if(val & O_SYNC)
	{
		printf(",synchronous writes");
	}

#if !defined (_POSIX_C_SOURCE)&& defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if(val & O_FSYNC)
	{
		printf(",synchronous,writes");
	}	
#endif
	putchar('\n');
	exit(0);
}
