#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{
	struct termios term;
	speed_t speed;

	if(isatty(STDIN_FILENO) < 0)
	{
		printf("STDIN_FILENO is not a tty\n");
		return 0;
	}

	if(tcgetattr(STDIN_FILENO,&term) < 0)
	{
		printf("tcgetattr error\n");
	}

	if((speed = cfgetispeed(&term)) < 0)
	{
		printf("cfgetispeed error\n");
	}

	printf("The input baud rate : %d\n",speed);

	
	if((speed = cfgetospeed(&term)) < 0)
	{
		printf("cfgetispeed error\n");
	}

	printf("The output baud rate : %d\n",speed);

	return 0;
}
