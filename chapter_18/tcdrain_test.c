#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{

	printf("The first hello world!\n");
	if(tcflow(STDOUT_FILENO,TCOOFF) < 0)
	{
		printf("tcflow with TCOON error\n");
		return 0;
	}
	
	printf("The second hello world!\n");

	if(tcdrain(STDOUT_FILENO) < 0)
	{
		printf("tctrain error\n");
	}
	return 0;
}
