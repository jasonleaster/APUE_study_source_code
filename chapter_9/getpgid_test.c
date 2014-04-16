#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid = 0;
	
	printf("Current process ID:%d\n",getpid());
	
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid == 0)
	{
		printf("Current process group of child process ID: %d\n",getpgrp());
		exit(0);
	}
	else if(pid > 0)
	{
		waitpid(pid,NULL,0);
		printf("Current process group of parent process ID : %d\n",getpgrp());
	}

	return 0;
}
