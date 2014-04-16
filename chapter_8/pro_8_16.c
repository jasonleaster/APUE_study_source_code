/****************************************************************
code writer : EOF
code date : 2014.03.27
e-mail: jaosonleaster@gmail.com
attention:
	The ./a.out ./b.out problem is just simple "hello world"
program.If you want to use another program to repleace the program 
it is OK.
	
****************************************************************/
#include"apue.h"
#include"myerr.h"
#include"sys/wait.h"
char* env_init[] = {"USER=unknown" ,"PATH=/tmp",NULL};

int main()
{
	pid_t  pid;
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if( pid == 0)
	{
		if(execle("./a.out","a.out",(char*)0,env_init) < 0)
		{
			err_sys("execle error\n");
		}
	}
	else
	{
		if(waitpid(pid,NULL,0) < 0)
		{
			err_sys("wait error\n");
		}
		printf("parent\n");
	}
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid == 0)
	{
		if(execlp("./b.out","b.out",(char*) 0) < 0)
		{
			err_sys("execlp error\n");
		}
	}
	else
	{
		if(waitpid(pid,NULL,0) < 0)
		{
			err_sys("wait error\n");
		}
		printf("parent\n");
	}
	
	exit(0);
}

