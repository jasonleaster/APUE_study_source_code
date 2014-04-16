#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("The ttyname of STDIN_FILENO is %s\n",ttyname(STDIN_FILENO));

	printf("The ttyname of STDOUT_FILENO is %s\n",ttyname(STDOUT_FILENO));

	printf("The ttyname of STDERR_FILENO is %s\n",ttyname(STDERR_FILENO));

	return 0;
}
