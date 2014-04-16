#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5

jmp_buf jmpbuffer;

int main()
{
	char line[MAXLINE];
	
	if(setjmp(jmpbuffer) != 0)
	{
		printf("error\n");
	}

	while(fgets(line,MAXLINE,stdin) != NULL)
	{
		do_line(line);
	}
	
	
	return 0;
}

void cmd_add(void)
{
	int token;

	token = get_token();
	
	if(token < 0)
	{
		longjmp(jmpbuffer,1);
		//***
	}
}
