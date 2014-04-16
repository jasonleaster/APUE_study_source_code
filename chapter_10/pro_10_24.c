#include <apue.h>

static volatile sig_atomic_t sigflag;

static sigset_t newmask,oldmask,zeromask;

static void sig_usr(int signo)
{
	sigflag = 1;
}
	
void TELL_WAIT(void)
{
	struct sigaction act_usr1,act_usr2;
	
	sigemptyset(act_usr1.sa_mask);
	sigemptyset(act_usr2.sa_mask);
	
	act_usr1.flags = 0;
	act_usr2.flags = 0;
	
	act_usr1.sa_handler = sig_usr;
	act_usr2.sa_handler = sig_usr;

	if(sigaction(SIGUSR1,&act_usr1,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	if(sigaction(SIGUSR2,&act_usr2,NULL) < 0)
	{
		printf("sigaction error\n");
	}
	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&newmask,SIGUSR2);
	
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
	{
		printf("sigprocmask error\n");
	}
	
}

void TELL_PARENT(void)
{
	kill(pid,SIGUSR2);
}

void WAIT_PARENT(void)
{
	while(sigflag == 0)
	{
		sigsuspend(&zeromask);
	}
	
	sigflag = 0;
	
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		printf("sigprocmask error\n");
	}
}

void TELL_CHILD(pid_t pid)
{
	kill(pid,SIGUSR1);
}

void WAIT_CHILD(void)
{
	while(sigflag == 0)
	{
		sigsuspend(&zeromask);
	}
	
	sigflag = 0;
	
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		err_sys("SIG_SETMAKS error\n");
	}
}
	
