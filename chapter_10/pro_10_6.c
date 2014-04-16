#include "apue.h"
#include "sys/wait.h"
#include "stdio.h"
#include "myerr.h"

static void sig_cld(int signo);

int main()
{
	pid_t pid;
	
	if(signal(SIGCLD,sig_cld) == SIG_ERR)
	{
		perror("signal error\n");
	}
	
	if((pid = fork()) < 0)
	{
		perror("fork error\n");
	}
	else if(pid == 0)
	{
		sleep(2);
		_exit(0);
	}
	
	pause();
	exit(0);
}

static void
sig_cld(int signo)
{
	pid_t pid;
	int status;
	
	printf("SIGCLD received\n");
	if(signal(SIGCLD,sig_cld) == SIG_ERR)
	{
		printf("signal error\n");
	}
	
	if((pid = wait(&status)) < 0)
	{
		printf("wait error\n");
	}

	printf("pid %d\n",pid);
}
