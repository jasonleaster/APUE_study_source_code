#include"apue.h"
#include"sys/wait.h"
#include"myerr.h"

int main()
{
	pid_t pid;
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error!\n");
	}
	else if(pid == 0)
	{	
		//if(execl("/Ad_Pro_in_Unix/chapter_8/awkexample","awkexample",NULL) < 0)//this is for figure-21
		if(execl("./testinterp","testinterp",NULL) < 0)//this is fir figure-20
		{
			err_sys("execl error!\n");
		}
	}

	if(waitpid(pid,NULL,0) < 0)
	{
		err_sys("waitpid error!\n");
	}
	exit(0);
}
