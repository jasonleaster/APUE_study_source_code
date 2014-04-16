#include"apue.h"
#include"myerr.h"
#include"stdio.h"
#include<sys/wait.h>

int main()
{
	pid_t pid;
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error!\n");
	}
	else if(pid == 0)
	{
		if((pid = fork()) < 0)
		{
			err_sys("fork error\n");
		}
		else if(pid > 0)
		{
	/*		if(waitpid(pid,NULL,0) != pid)
			{
				printf("waitpid error\n");
			}
	
			printf("first child pid = %d\n",getpid());
	*/
			exit(0);
		}
	
		sleep(2);
		printf("\nsecond child, parent getppid =%d second child pid = %d\n",getppid(),getpid());
		exit(0);
	}
	
	if(waitpid(pid,NULL,0) != pid)
	{
		err_sys("waitpid error\n");
	}
	
	printf("parent pid = %d \n",getppid());
	exit(0);
}
