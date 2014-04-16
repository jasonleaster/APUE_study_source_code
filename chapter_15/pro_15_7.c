#include <stdio.h>
#include <fcntl.h>

static pfd1[2],pfd2[2];

void TELL_WAIT(void)
{
	if(pipe(fpd1) < 0 || pipe(pfd2) < 0)
	{
		printf("pipe error\n");
	}
}

void TELL_PARENT(void)//tell to parent
{
	if(write(pfd2[1],"c",1) != 1)
	{
		printf("write error\n");
	}
}

void WAIT_PARENT(void)//wait for parent
{
	char c;
	
	if(read(pfd1[0],&c,1) != 1)
	{
		printf("read error\n");
	}

	if(c != 'p')
	{
		printf("WAIT_PARENT: incorrect data\n");
	}
}

void TELL_CHILD(pid_t pid)//tell to child
{
	if(write(pfd1[1],"p",1) != 1)
	{
		printf("write error\n");
	}
}

void WAIT_CHILD(void)//wait for child
{
	char c;
	if(read(pdf2[0],&c,1) != 1)
	{
		printf("read error\n");
	}

	if(c != 'c')
	{
		printf("WAIT_CHILD : incorrect data\n");
	}
}
