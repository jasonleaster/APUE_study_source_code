/****************************************************************************
code writer : EOF
code date : 2014.04.08
e-mail : jasonleaster@gmail.com
code purpose:
	Just a demonstartion for mandatory locking
If there is something wrong with my code, please touch me by e-mail.

****************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <myerr.h>

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

int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	return fcntl(fd,cmd,&lock);
}

void child_handler(int signo)
{
	//Nothing to be done. Just a empty handler
}

int main(int argc, char* argv[])
{
	int 		fd;
	pid_t		pid;
	char	 	buf[5];
	struct stat	statbuf;

	if(argc != 2)
	{
		fprintf(stderr,"usage :%s filename\n",argv[0]);
		exit(1);
	}

	if((fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IXUSR)) < 0)
	{
		err_sys("open error\n");
		return 0;
	}

	if(write(fd,"abcdef",6) != 6)
	{
		err_sys("write error\n");
		return 0;
	}

	if(fstat(fd,&statbuf) < 0)
	{
		err_sys("fstat error\n");
	}

	if(fchmod(fd,(statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
	{
		err_sys("fchmod error\n");
		return 0;
	}

	if((pid = fork()) < 0)
	{
		err_sys("for error\n");
	}
	else if(pid > 0)
	{
		//write lock
		if(lock_reg(fd,F_SETLK,F_WRLCK,0,SEEK_SET,0) < 0)
		{
			printf("parent lock_reg error\n");
		}
		sleep(1);
		//It's neccessay to sleep for a few second to 
		//let the child install the signal handler first.
		kill(pid,SIGUSR1);
		
		if(waitpid(pid,NULL,0) < 0 )
		{
			err_sys("waitpid error\n");
		}
	}
	else
	{
		struct sigaction sa;

		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = child_handler;
		sigaddset(&sa.sa_mask,SIGUSR1);
	
		if(sigaction(SIGUSR1,&sa,NULL) < 0)
		{
			printf("child sigaction error\n");
			return 0;
		}

		pause();//wait to caught the signal
	
		set_fl(fd,O_NONBLOCK);
	
		//read lock
		if(lock_reg(fd,F_SETLK,F_RDLCK,1,SEEK_SET,0) != -1)
		{
			printf("child : read lock succeeded\n");
		}
		
		printf("read lock of alredy-locked region returns %d \n",errno);
	
		if(lseek(fd,0,SEEK_SET) < 0)
		{
			err_sys("lseek error\n");
		}

		if(read(fd,buf,2) < 0)
		{
			err_ret("read failed (mandatory locking works)\n");
		}
		else
		{
			printf("read OK (no mandatory locking),buf = %2.2s\n",buf);
		}

		return 0;
	}
	exit(0);
}
