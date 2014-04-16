/***************************************************************************
code writer :EOF
code date : 2014.03.25
e-mail : jasonleaster@gmail.com
code purpose:
	just a demo for uname function. I would like to share my code with
you. If you find something thing wrong with my code, please touche me 
by e-mail. Thank you!

****************************************************************************/
#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>

int main()
{
	struct utsname* p_utsname = NULL;
	
	if((p_utsname = (struct utsname*)malloc(sizeof(struct utsname))) == NULL)
	{
		printf("malloc error\nprocess end\n");
		return 0;
	}	

	if((uname(p_utsname)) < 0)
	{
		printf("uname error\n");
	}
	else
	{
		printf("name of the operating system:%s\n",p_utsname->sysname);
		printf("name of this node:%s\n",p_utsname->nodename);
		printf("current release of operating system:%s\n",p_utsname->release);
		printf("current version of this release:%s\n",p_utsname->version);
		printf("name of hard ware type:%s\n",p_utsname->machine);
	}
	
	free(p_utsname);
	return 0;
}
