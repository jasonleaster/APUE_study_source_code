#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("getenv returned value:%s\n",getenv("HOME"));
	return 0;
}
