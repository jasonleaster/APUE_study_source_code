#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("uid : %d\n",getuid());

	if(setuid(0) < 0)
	{
		printf("setuid error\n");
		return 0;
	}
	else
	{
		printf("uid :%d\n",getuid());
	}

	return 0;
}
