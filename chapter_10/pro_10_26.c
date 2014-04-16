#include <apue.h>

static void sig_int(int signo)
{
	printf("caught SIGINT\n");
}

static void sig_child(int signo)
{
	printf("caught SIGCHILD\n");
}

int main()
{
	struct sigaction act_int,act_child;
	
	act_int.sa_flags = 0;
	act_child.sa_flags = 0;
	
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_child.sa_mask);
	
	act_int.sa_handler = sig_int;
	act_child.sa_handler = sig_child;

	if(sigaction(SIGINT,&act_int,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	if(sigaction(SIGCHLD,&act_child,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	if(system("/bin/ed") < 0)
	{
		printf("system() error\n");
	}
	
	exit(0);
}
