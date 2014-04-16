#include <stdio.h>
#include "apue.h"

#define TOK_ADD 5

void do_line(char*);
void cmd_add(void);
int get_token(void);

int main()
{
	char line[MAXLINE];
	
	while(fgets(line,MAXLINE,stdin) != NULL)
	{
		do_line(line);
	}

	return 0;
}

char *toke_ptr;

void do_line(char* ptr)
{
	int cmd;

	tok_ptr = ptr;
	while((cmd = get_token()) > 0)
	{
		switch(cmd)
		{
			case TOK_ADD:
				cmd_add();
				break;
		}
	}
}


void cmd_add(void)
{
	int token;
	
	token = get_token();
		
}

int get_toke(void)
{
	
}






