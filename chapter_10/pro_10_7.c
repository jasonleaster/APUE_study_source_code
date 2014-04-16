#include"apue.h"
#include"unistd.h"

static void 
sig_alrm()
{
	//
}

unsigned int
sleep1(unsigned int nsecs)
{
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
	{
		return (nsecs);
	}
	alarm(nsecs);
	pause();
	return (alarm(0));
}
