#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#ifndef TIOCGWINSZ
	#include <sys/ioctl.h>
#endif

static void pr_winsize(int fd)
{
	struct winsize size;
	
	if(ioctl(fd,TIOCGWINSZ,(char *)&size) < 0)
	{
		printf("ioctl error\n");
	}

	printf("%d rows, %d columns\n",size.ws_row,size.ws_col);
}

static void sig_winch(int signo)
{
	printf("SIGWINCH received\n");
	pr_winsize(STDIN_FILENO);
}

int main()
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_winch;

	if(isatty(STDIN_FILENO) == 0)
	{
		return 1;
	}

	if(sigaction(SIGWINCH,&sa,NULL) < 0)
	{
		printf("sigaction error\n");
	}

	pr_winsize(STDIN_FILENO);

	for(;;)
	{
		pause();
	}

	return 0;
}
