#include <apue.h>

volatile sig_atomic_t quitflag = 0;
	
static void sig_int(int signo)
{
	if(signo == SIGINT)
	{
		printf("\ninterrupt\n");
	}
	else if(signo == SIGQUIT)
	{
		quitflag = 1;
	}
}

int main()
{
	sigset_t newmask,oldmask,zeromask;
	
	struct sigaction act_int,act_qt;
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_qt.sa_mask); 
	act_int.sa_flags = 0;
	act_qt.sa_flags  = 0;

	sigemptyset(&newmask);
	sigemptyset(&oldmask);
	sigemptyset(&zeromask);
	
	act_int.sa_handler = sig_int;
	act_qt.sa_handler  = sig_int;

	if(sigaction(SIGINT,&act_int,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	if(sigaction(SIGQUIT,&act_qt,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_qt.sa_mask);
	sigaddset(&act_int.sa_mask,SIGINT);
	sigaddset(&act_qt.sa_mask,SIGQUIT);
	
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
	{
		printf("SIG_BLOCK error\n");
	}
	
	while(quitflag == 0)
	{
		sigsuspend(&zeromask);
	}
	
	quitflag = 0;
	
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		printf("sigprocmask error\n");
	}
	
	printf("\n");
	
	exit(0);
}


