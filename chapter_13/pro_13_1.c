/*
I still don't know what's wrong with my program.....
*/

#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <myerr.h>

void daemonize(const char * cmd)
{
	int	i,fd0,fd1,fd2;
	pid_t	pid;
	struct  rlimit 	 rl;
	struct  sigaction sa;

	umask(0);

	if(getrlimit(RLIMIT_NOFILE,&rl) < 0)
	{
		err_quit("%s: can't get file limit",cmd);
	}

	if((pid = fork()) < 0)
	{
		err_quit("%s : can't fork",cmd);
	}
	else if(pid != 0)
	{
		exit(0);
	}

	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if((sigaction(SIGHUP,&sa,NULL)) < 0)
	{
		err_quit("%s can't fork\n",cmd);
	}

	if((pid = fork()) < 0)
	{
		err_quit("%s : can't fork",cmd);
	}
	else if (pid != 0)
	{
		exit(0);
	}

	if(chdir("/")  <  0)
	{
		err_quit("%s can't change dirctory to /\n");
	}

	if(rl.rlim_max == RLIM_INFINITY)
	{
		rl.rlim_max = 1024;
	}

	for(i = 0; i < rl.rlim_max;i++)
	{
		close(i);
	}

	fd0 = open("/dev/null",O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd,LOG_CONS,LOG_DAEMON);
	
	sleep(12);
	if(fd0  != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR,"unexpected file deacriptors %d %d %d\n",fd0,fd1,fd2);
		exit(1);
	}
}
/*
int main()
{
	daemonize("hello world!\n");
	return 0;
}
*/
