#include <stdio.h>
#include <pthread.h>
#include <syslog.h>
#include <signal.h>

sigset_t mask;

extern int already_running(void);

void reread(void)
{
	/**/
}

void* thr_fn(void*arg)
{
	int err,signo;
	for(;;)
	{
		err = sigwait(&wait,&signo);
		if(err != 0)
		{
			syslog(LOG_ERR,"sigwait failed");
			exit(1);
		}
	
		switch(signo)
		{
			case SIGHUP:
			{
				syslog(LOG_INFO,"Re-reading configuration file");
				reread();
				break;
			};

			case SIGTERM:
			{
				syslog(LOG_INFO,"got SIGTERM; exiting");
				exit(0);
			};
		
			default:
				syslog(LOG_INFO,"unexpected signal %d\n",signo);
			
		}
	}
	
	return 0;

}

int main(int argc,char* argv[])
{
	int err;
	int tid;
	char *cmd;
	struct sigaction sa;
	
	if((cmd = strrchr(argv[0],'/')) == NULL)
	{
		cmd = argv[0];
	}
	else
	{
		cmd++;
	}
	
	daemonize(cmd);

	if(already_running())
	{
		syslog(LOG_ERR,"daemon already running\n");
		exit(0);
	}

	sa.sa_handler = SIG_DEL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction (SIGHUP,&sa,NULL) < 0)
	{
		err_quit("%s: can't restore SIGHUP default\n");
	}

	sigfillset(&mask);
	if((err = pthread_sigmask(SIG_BLOCK,&mask,NULL)) != 0)
	{
		err_exit(err,"SIG_BLOCK error\n");
	}

	err = pthread_create(&tid,NULL,thr_fn,0);
	
	if(err != 0)
	{
		err_exit(err,"can't create thread\n");
	}

	exit(0);
}
