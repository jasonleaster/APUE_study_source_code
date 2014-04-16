#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	struct termios term;
	
	if(tcgetattr(STDIN_FILENO,&term) < 0)
	{
		printf("tcgetattr error\n");
	}

	switch(term.c_cflag & CSIZE)
	{
		case CS5 :
		printf("5 bits/byte\n");
		break;

		case CS6:
		printf("6 bits/byte\n");
		break;

		case CS7 :
		printf("7 bits/byte\n");
		break;

		case CS8 :
		printf("8 bits/byte\n");
		break;
		
		default :
			printf("unknown bits/byte\n");
	}

	term.c_cflag &= ~CSIZE;
	term.c_cflag |= CS8;
	
	if(tcsetattr(STDIN_FILENO,TCSANOW,&term) < 0)
	{
		printf("tcsetattr error\n");
	}

	return 0;
}
