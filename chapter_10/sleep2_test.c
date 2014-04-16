#include"apue.h"
#include"signal.h"
#include"unistd.h"
#include"setjmp.h"

static jmp_buf env_alrm;

static void 
sig_alrm(int signo)
{	
	printf("signal received\n");
	longjmp(env_alrm,1);
	printf("finished longjmp\n");
}

unsigned int
sleep2(unsigned int nsecs)
{
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
	{
		return (nsecs);
	}
	printf("setjmp\n");
	if(setjmp(env_alrm) == 0)
	{
		printf("hello world!\n");
		alarm(nsecs);
		pause();
	}
	printf("after setjmp\n");
	
	return (alarm(0));
}

int main()
{
	sleep2(5);
	return 0;
}

