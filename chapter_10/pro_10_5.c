#include"apue.h"
#include<pwd.h>
#include"myerr.h"

static void 
my_alarm(int signo)
{
	struct passwd* rootptr;
	
	printf("in signal handler\n");
	if((rootptr = getpwnam("root")) == NULL)
	{
		err_sys("getpwnam(root) error\n");
	}
	
	alarm(1);
}

int main()
{
	struct passwd *ptr;
	
	signal(SIGALRM,my_alarm);
	alarm(1);
	for( ; ; )
	{
		if((ptr = getpwnam("liuzjian")) == NULL)
		{
			err_sys("getpwnam error\n");
		}
	
		if(strcmp(ptr->pw_name,"liuzjian") != 0)
		{
			printf("return vale corrupted!,pw_name %s\n",ptr->pw_name);
		}
	}
}
