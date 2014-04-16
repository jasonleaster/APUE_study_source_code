/*********************************************************************************
code writer : EOF
code date : 2014.04.01
e-mail: jasonleaster@gmail.com

code purpose :
	just a demo for siglongjmp and sigsetjmp
	
	I would like to share my code with someone. Sharing make our imporve 
together. Just share your code with us. Open source make our world better and
 better. If there are something wrong with my code, please touch me by e-mail.
Thank you. I am glad to receive your feedback.

*********************************************************************************/
#include <setjmp.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <myerr.h>

static void		sig_usr1(int),sig_alrm(int);
static sigjmp_buf		jmpbuf;
static volatile	sig_atomic_t	canjump;

void  pr_mask(const char* str);


int main()
{
	struct sigaction act_usr,act_alrm;
	act_usr.sa_flags  = 0;
	act_alrm.sa_flags = 0;//you may initialize the sa_flags. There are some bit operation on these varibles.
	
	act_usr.sa_handler = sig_usr1;
	sigemptyset(&act_usr.sa_mask);
	act_usr.sa_flags = 0;
	
	if(sigaction(SIGUSR1,&act_usr,NULL) <0)
	{
		printf("sigaction error\n");
	}
	
	act_alrm.sa_handler = sig_alrm;
	sigemptyset(&act_alrm.sa_mask);
	act_alrm.sa_flags |= SA_INTERRUPT;
	
	if(sigaction(SIGALRM,&act_alrm,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	pr_mask("starting main:\n");

	if(sigsetjmp(jmpbuf,1))
	//reset the signal mask if the second parameter of sigsetjmp is non-zero.
	//If the second parameter is zero,the maskwould be leave.
	{
		pr_mask("ending main\n");
		exit(0);
	}
	
	canjump = 1;//now setjmp is OK

	for( ; ;)
	{
		pause();
	}
		
}


static void
sig_usr1(int signo)
{
	time_t	starttime;
	
	if(canjump == 0)
	{
		return;
	}
	
	pr_mask("starting usr1:\n");

	alarm(3);
	starttime = time(NULL);
	
	for( ; ;)
	{
		if(time(NULL) > starttime +5)
		{
			break;
		}
	}

	pr_mask("finishing sig_usr1:\n");
	
	canjump = 0;
	
	siglongjmp(jmpbuf,0);
}

static void 
sig_alrm(int signo)
{
	pr_mask("in sig_alrm\n");
}

void 
pr_mask(const char* str)
{
	sigset_t sigset;
	int errno_save;
	
	errno_save = errno;
	
	if(sigprocmask(0,NULL,&sigset) < 0)
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
