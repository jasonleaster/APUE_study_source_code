#include <stdio.h>
#include <unistd.h>

int main()
{
	int file_descriptor = 0;
	
	if((file_descriptor = open("/dev/tty","r")) < 0)
	{
		printf("open error\n");
	}

	printf("foregroup ID:%d\n",tcgetpgrp(file_descriptor));

	close(file_descriptor);
	return 0;
}
