#include <setjmp.h>
#include <myerr.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include </Ad_Pro_in_Unix/chapter_10/pro_10_14.c>
//pro_10_14.c is the implementation of pr_mask. I have show the definition of  pr_mask in this blog.

static void sig_int(int signo);

int main()
{
	sigset_t newmask,oldmask,waitmask;
	struct sigaction act_int,oact_int;

	sigemptyset(&act_int.sa_mask);

	sigemptyset(&newmask);
	sigemptyset(&oldmask);
	sigemptyset(&waitmask);//initialize the signal mask.

	act_int.sa_handler = sig_int;
	act_int.sa_flags = 0;//I don't use flags. You know, it is bits operation and nothing would be set if the flag is zero.

	pr_mask("program start: \n");
	
	if(sigaction(SIGINT,&act_int,NULL) < 0)
	{
		printf("sigaction error\n");
	}

	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)//add the newmask's bits into oldmask
	{
		printf("sigprocmask error\n");
	}
	
	pr_mask("in critical region\n");
	
	if(sigsuspend(&waitmask) != -1)// suspend the signal in waitmask.
	{
		err_sys("sigprocmask error\n");
	}

	pr_mask("after return from sigsuspend\n");

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		printf("sigprocmask error\n");
	}
		
	pr_mask("program exit\n");

	return 0;
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int\n");
}
