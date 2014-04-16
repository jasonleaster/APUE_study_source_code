#include <stdio.h>

extern char** environ;

int main()
{
	int temp = 0;

	while(*(environ+temp) != NULL)
	{
		printf("%s\n",*(environ+temp));
		temp++;
	}

	return 0;	
}

