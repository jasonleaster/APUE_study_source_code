#include <apue.h>
#include <errno.h>

void 
pr_mask(const char* str)
{
	sigset_t sigset;
	int errno_save;
	
	errno_save = errno;
	
	if(sigprocmask(0,NULL,&sigset) < 0)
	// block current signal and save the current mask in sigset.
	//the second parameter of sigprocmask is NULL and current mask is not changed.
	{
		err_sys("sigprocmask error\n");
	}
	
	printf("%s",str);

	if(sigismember(&sigset,SIGINT)) 
	{
		printf("SIGINT\n");
	}

	if(sigismember(&sigset,SIGQUIT)) 
	{
		printf("SIGQUIT\n");
	}

	if(sigismember(&sigset,SIGUSR1)) 
	{
		printf("SIGUSR1\n");
	}

	if(sigismember(&sigset,SIGALRM)) 
	{
		printf("SIGALRM\n");
	}
	
	errno = errno_save;

}
