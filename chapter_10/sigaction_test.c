/*******************************************************************
code writer :EOF
code date : 2014.04.01
e-mail:jasonleaster@gmail.com

code purpose :
	I would like to share my code with people who is interesting
in APUE. Sharing make our improve together. If you find there is 
something wrong with my code, please touch me by e-mail. Thank you.

*******************************************************************/
#include <stdio.h>
#include <signal.h>

void signal_handler(int signo);

int main()
{
	struct sigaction act;
	
	act.sa_handler = signal_handler;
	
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;//don't use flags
	
	if(sigaction(SIGUSR1,&act,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	kill(getpid(),SIGUSR1);	
	sleep(2);//avoid to exit rapaidly so that the signal handler didn't finish
	return 0;
}

void signal_handler(int signo)
{
	printf("signal received\n");
}


