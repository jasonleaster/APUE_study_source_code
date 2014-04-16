#include"apue.h"
#include"myerr.h"

int main()
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid != 0)
	{
		sleep(2);//I wonder why not to use waitpid.......
		exit(2);
	}
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid != 0)
	{
		sleep(4);
		abort();
	}
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid != 0 )
	{
		execl("/bin/dd","dd","if=/etc/termcap","of=/dev/null",NULL);
		exit(7);
	}
	
	if((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if(pid != 0)
	{
		sleep(8);
		exit(0);
	}

	sleep(6);
	kill(getpid(),SIGKILL);
	exit(6);
}
