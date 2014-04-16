#include <stdio.h>
#include <signal.h>

int main()
{
	psignal(SIGCHLD,"hello world");	
	return 0;
}
