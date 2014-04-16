#include <apue.h>
#include <myerr.h>

int main()
{
	int n ;
	char line[MAXLINE];
	
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
	{
		err_sys("signal (SIGALRM) error\n");
	}
	
	alarm(10);
	if((n = read(STDIN_FILENO,line,MAXLINE)) < 0)
	{
		err_sys("read error\n");
	}
	alarm(0);

	write(STDOUT_FILENO,line,n);
	exit(0);
}

static void
sig_alrm(int signo)
{
	//
}
