#include <stdio.h>
#include "string.h"
#define BUFFSIZE 10

int main()
{
	char buffer[BUFFSIZE];
	int byte = 0;

	memset(buffer,0,sizeof(char)*BUFFSIZE);

	setbuf(stdout,buffer);
	fread(buffer,sizeof(char),BUFFSIZE-1,stdin);
	fflush(stdin);
	fwrite(buffer,sizeof(char),BUFFSIZE-1,stdout);
	fflush(stdout);
	return 0;
}
