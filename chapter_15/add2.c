#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096

int main()
{

	char line[MAXLINE];

	while(fgets(line,MAXLINE,stdin) != NULL)
	{
		fputs(line,stdout);
	}
	return 0;
}
