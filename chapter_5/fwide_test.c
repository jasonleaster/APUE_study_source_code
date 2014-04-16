#include "stdio.h"
#include "string.h"

#define BUFFSIZE 1024
#define POSITIVE 1

int main()
{
	FILE* file_pointer = NULL;
	char buffer[BUFFSIZE];
	
	int byte = 0;
	
	memset(buffer,0,BUFFSIZE*sizeof(char));

	file_pointer = fopen("./test.txt","r+");
	
	if(file_pointer == NULL)
	{
		printf("fopen error\n");
		return 0;
	}
	
	fwide(file_pointer,POSITIVE);

	while((byte = fread(buffer,4*sizeof(char),BUFFSIZE,file_pointer)) > 0)
	{
		fwrite(buffer,4*sizeof(char),byte,stdout);
	}

	printf("\n");
	fclose(file_pointer);
	return 0;
}
