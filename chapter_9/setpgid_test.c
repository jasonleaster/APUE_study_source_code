#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid = 0;
	
	printf("Current process -- parent process ID:%d\n",getpid());
	
	printf("Current process group of parent process ID : %d\n",getpgrp());

	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid == 0)
	{
		pid_t pgrp;

		printf("child process ID:%d\n",getpid());
		
		printf("Current process group of child process ID: %d\n",getpgrp());
		
		printf("after set new group\n");
		
	/*	if(setpgid(getpid(),0) < 0)
		{
			printf("second setpgid error\n");
			exit(0);
		}
	*/
		setsid();
		
		printf("Current process group of child process ID: %d\n",getpgrp());
		printf("Current sessions ID :%d\n",getsid(getpid()));
		exit(0);
	}
	else if(pid > 0)
	{
		waitpid(pid,NULL,0);
		printf("Current process group of parent process ID : %d\n",getpgrp());
		printf("Current session ID of parent process : %d\n",getsid(getpid()));
	}

	return 0;
}
