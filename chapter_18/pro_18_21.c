#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include </Ad_Pro_in_Unix/chapter_18/pro_18_20.c>

static void sig_catch(int signo)
{
	printf("signal caught\n");
	tty_reset(STDIN_FILENO);
	return;
}

int main()
{
	int i;
	char c;
	struct sigaction sa_INT,sa_TERM;
	
	sigemptyset(&sa_INT.sa_mask);
	sigemptyset(&sa_TERM.sa_mask);
	sa_INT.sa_flags = 0;
	sa_TERM.sa_flags = 0;
	sa_TERM.sa_handler = sig_catch;
	sa_INT.sa_handler = sig_catch;
	
	if(sigaction(SIGINT,&sa_INT,NULL) < 0)
	{
		printf("SIGINT sigaction error\n");
	}

	if(sigaction(SIGTERM,&sa_TERM,NULL) < 0)
	{
		printf("SIGTERM sigaction error");
	}

	if(tty_raw(STDIN_FILENO) < 0)
	{
		printf("tty_raw error\n");
	}

	printf("Enter raw mode charaters, terminate with DELETE\n");

	while((i = read(STDIN_FILENO,&c,1)) == 1)
	{
		if((c &= 255) == 0177)
		{
			break;
		}

		printf("%o\n",c);
	}

	if(i <= 0)
	{
		printf("read error\n");
	}

	if(tty_cbreak(STDIN_FILENO) < 0)
	{
		printf("tty_cbreak error\n");
	}

	printf("\nEnter cbreak mode characters, terminate with SIGINT\n");
	while((i = read(STDIN_FILENO,&c,1)) == 1)
	{
		c &= 255;
		printf("%o\n",c);
	}

	if(tty_reset(STDIN_FILENO) < 0)
	{
		printf("tty_reset error\n");
	}

	if(i <= 0)
	{
		printf("read error\n");
	}

	return 0;
}
