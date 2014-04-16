#include <stdio.h>
#include <termio.h>
#include <unistd.h>

int main()
{
	struct termios term;
	long vdisable;

	if(isatty(STDIN_FILENO) == 0)
	{
		printf("standard input is not a terminal device\n");
		return 0;
	}

	if((vdisable = fpathconf(STDIN_FILENO,_PC_VDISABLE)) < 0)
	{
		printf("fpathconf error or _POSIX_VDISABLE not in effect\n");
		return 0;
	}

	if(tcgetattr(STDIN_FILENO,&term) < 0)
	{
		printf("tcgetattr error\n");
	}

	term.c_cc[VINTR] = vdisable;
	term.c_cc[VEOF]  = 2;
	
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&term) < 0)
	{
		printf("tcsetattr error\n");
		return 0;
	}

	return 0;
}
