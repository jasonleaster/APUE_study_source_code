#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t temp = 0;
	//test pid_t getpgrp(void);
	printf("The group ID of current process : %d\n",getpgrp());
	
	//test pid_t getpgrp(pid_t pid);
	printf("The group ID of current process : %d\n",getpgid(getpid()));
	return 0;
}
