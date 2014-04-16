/*************************************************************
code writer : EOF
code date : 2014.03.28
e-mail: jasonleaster@gmail.com
code purpose :
	I just share my demo with who is interesting in APUE.
Open source make the world more beautiful. I would like to 
recept your feedback, if there is something wrong with my code.
Please touch me by e-mail. Thank you

*************************************************************/
#include <stdio.h>
#include <apue.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE >= 200809L
#endif

int main()
{
	int pid  = 0;
	int status = 0;
	siginfo_t* p_siginfo = NULL;
	
	p_siginfo = (siginfo_t*)malloc(sizeof(siginfo_t));
	
	if(p_siginfo == NULL)
	{
		printf("malloc error\n");
		return 0;
	}

	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid == 0)
	{
		printf("hello! I am the child %d\n",getpid());
		exit(0);
	}

/*	if(waitpid(pid,&status,0) < 0 )
	{
		printf("waitpid error\n");
	}
*/

	int temp = 0;
	if((temp = waitid(P_ALL,pid,p_siginfo,WNOWAIT)) < 0)// why there would return -1
	{
		printf("waitid error\n");
	}	

	if(WIFEXITED(status))
	{
		printf("normally termination,exit status = %d\n",status);
	}
	
	printf("parent exit\n");
	
	free(p_siginfo);
	return 0;
}
