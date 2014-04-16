/**********************************************************
code writer : EOF
code date : 2014.03.31
e-mail : jasonleaster@gmail.com
code purpose :
	I would like to share my code with someone like me.
Just a demo for signal function. The signal would be loaded
to stack.Load once, pop once.

***********************************************************/

#include"apue.h"
#include"stdio.h"
#include"myerr.h"

static void sig_usr(int);

int main()
{
	int temp = 0;

	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
	{
		err_sys("signal error\n");
	}	

	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
	{
		err_sys("can't catch SIGUSR2");
	}
	
	for(temp = 0;1;temp++)
	{	
		pause();

		if(temp < 1)
		{
			if(signal(SIGUSR1,sig_usr) == SIG_ERR)
			{
				err_sys("signal error\n");
			}	

			if(signal(SIGUSR2,sig_usr) == SIG_ERR)
			{
				err_sys("can't catch SIGUSR2");
			}
		}
	}		
	
	return 0;
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("received SIGUSR1\n");
	}
	else if(signo == SIGUSR2)
	{
		printf("received SIGUSR2\n");
	}
	else
	{
		err_dump("received signal %d\n",signo);
	}
}

