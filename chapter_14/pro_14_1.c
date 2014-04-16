#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <myerr.h>

#define BUFFSIZE 500000

void set_fl(int fd,int flags)
{
	int val;
	
	if((val = fcntl(fd,F_GETFL,0)) < 0)
	{
		err_sys("fcntl F_GETFL error\n");
	}

	val |= flags;
	
	if(fcntl(fd,F_SETFL,val) < 0)
	{
		err_sys("fcntl F_SETEL error\n");
	}
}

void clr_fl(int fd,int flags)
{
	int val;
	
	if((val = fcntl(fd,F_GETFL,0)) < 0)
	{
		err_sys("fcntl F_GETFL error\n");
	}

	val &= ~flags;
	
	if(fcntl(fd,F_SETFL,val) < 0)
	{
		err_sys("fcntl F_SETEL error\n");
	}
}

char buf[BUFFSIZE];

int main()
{
	int ntowrite,nwrite;
	char	*ptr;
	
	ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr,"read %d bytes\n",ntowrite);

//	set_fl(STDOUT_FILENO,O_NONBLOCK);
	set_fl(STDOUT_FILENO,0);

	ptr = buf;
	
	while(ntowrite > 0)
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO,ptr,ntowrite);
		fprintf(stderr,"nwrite = %d,errno %d\n",nwrite,errno);
		
		if(nwrite > 0)
		{
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_fl(STDOUT_FILENO,O_NONBLOCK);
	
	exit(0);
}
