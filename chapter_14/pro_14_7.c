/***********************************************************************************************
code write : EOF
code date : 2014.04.08
e-mail: jasonleaster@gmail.com

code purpose :
	Just a demo for deadlock
************************************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <myerr.h>
#include <signal.h>


int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	return fcntl(fd,cmd,&lock);
}

static void lockabyte(const char *name,int fd,off_t offset)
{
	if(lock_reg(fd,F_SETLKW,F_WRLCK,offset,SEEK_SET,1) < 0)
	{
		err_sys("%s: lock_reg error\n",name);
	}

	printf("%s got the lock,byte %ld\n",name,offset);
}

void parent_handler(int signo)
{
	if(waitpid(-1,NULL,0) < 0)
	{
		printf("waitpid error\n");
	}
}

void child_handler(int signo)
{
/*	if(waitpid(getppid(),NULL,0) < 0)
	{
		printf("waitpid error\n");
	}
*/
}

int main()
{
	int fd;
	pid_t pid;
//-----------------------initialize the signal handler-------------------------------------	
	struct sigaction sa_parent,sa_child;

	sigemptyset(&sa_parent.sa_mask);
	sa_parent.sa_flags = 0;
	sa_parent.sa_handler = parent_handler;
	
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;
	sa_child.sa_handler = child_handler;
	
	if(sigaction(SIGUSR1,&sa_parent,NULL) < 0)
	{
		printf("parent sigaction error\n");
		return 0;
	}

	
	if(sigaction(SIGUSR2,&sa_child,NULL) < 0)
	{
		printf("child sigaction error\n");
		return 0;
	}

//-----------------------------------------------------------------------------------------	
	if((fd = creat("./templock",(S_IRUSR|S_IWUSR|S_IXUSR))) < 0)
	{
		err_sys("creat error\n");
	}

	if(write(fd,"ab",2) != 2)
	{
		err_sys("write error\n");
	}

	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid == 0)
	{
		lockabyte("child",fd,0);
	//	TELL_PARENT(getppid());
		kill(getppid(),SIGUSR1);
	//	WAIT_PARENT();
/*
		if(waitpid(getppid(),NULL,0) < 0)
		{
			printf("waitpid error in child process\n");
			return 0;
		}
*/
		lockabyte("child",fd,1);
	}
	else
	{
		lockabyte("parent",fd,1);
//		TELL_CHILD(pid);
		kill(pid,SIGUSR2);
//		WAIT_CHILD();
/*		if(waitpid(pid,NULL,0) < 0)
		{
			printf("waitpid error in parent process\n");
			return 0;
		}
*/
		lockabyte("parent",fd,0);
	}

	exit(0);
}
