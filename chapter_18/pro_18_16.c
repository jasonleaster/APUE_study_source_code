/************************************************************
code writer : EOF
code date   : 2014.04.15 00:32
e-mail      : jasonleaster@gmail.com
code purpose:

	Just a demo for ourselves' ttyname--tty.There would 
be conflict with libc when we use our function's name 
as ttyname. So I change the name of the function into tty.
It's Nothing.

***********************************************************/

#include <stdio.h>
#include </Ad_Pro_in_Unix/chapter_18/pro_18_15.c>


int main()
{
	char* name;
	
	if(isatty(0))
	{
		name = tty(0);
		if(name == NULL)
		{
			name = "undefined\n";
		}
	}
	else
	{
		name = "not a tty\n";
	}

	printf("fd 0 :%s\n",name);

	if(isatty(1))
	{
		name = tty(1);
		if(name == NULL)
		{
			name = "undefined\n";
		}
	}	
	else
	{
		name = "not a tty\n";
	}
	

	printf("fd 1 :%s\n",name);


	if(isatty(2))
	{
		name = tty(2);
		if(name == NULL)
		{
			name = "undefined\n";
		}
	}	
	else
	{
		name = "not a tty\n";
	}
	
	printf("fd 2 :%s\n",name);
	
	return 0;
}
