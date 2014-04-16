/***************************************************************************
code writer :EOF
code date : 2014.03.25
e-mail : jasonleaster@gmail.com
code purpose:
	just a demo for gethostname function. I would like to share my code with
you. If you find something thing wrong with my code, please touche me 
by e-mail. Thank you!

****************************************************************************/
#include <unistd.h>
#include <stdio.h>

int main()
{
	char buffer[BUFSIZ];
	
	if(gethostname(buffer,BUFSIZ) != 0)
	{
		printf("gethostname error\n");
	}
	else
	{
		printf("host name:%s\n",buffer);
	}	
	
	return 0;
}
