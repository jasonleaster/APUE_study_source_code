#include "stdio.h"
#include "string.h"

#define BUFFSIZE 1024

int main()
{

	FILE* file_pointer = NULL;
	
	char buffer[BUFFSIZE];
	
	memset(buffer,0,sizeof(char)*BUFFSIZE);
	
	if((file_pointer = fopen("test.txt","r"))  == NULL)
	{
		printf("fopen error\n");
	}
	
	if((file_pointer = freopen("test.txt","r+",file_pointer)) == NULL)
	{
		printf("freopen error\n");
	}

	if(fread(buffer,sizeof(char),BUFFSIZE,file_pointer) < 0)
	{
		printf("fread error\n");
	}

	if(fwrite(buffer,sizeof(char),BUFFSIZE,stdout) != BUFFSIZE)
	{
		printf("fwrite error\n");
	}

	//fflush(stdout);
	fclose(file_pointer);

	return 0;
}
