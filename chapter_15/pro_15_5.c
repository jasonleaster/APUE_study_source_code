/*******************************************************************
code writer :EOF
code date : 2014.04.10
e-mail : jasonleaster@gmail.com

code purpose :
	Just a changed and test demo.
	If there is something wrong with my code, please touch me by
e-mail. If you know about why there is no competition between the child
process and parent process when they "read" and "write", please touch
me. I am very happy to share my code with you. Wish it could
help you to understand pipe. Thank you.

*******************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLINE 4096

int main()
{
	int 	n;
	int 	fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if(pipe(fd) < 0)
	{
		printf("pipe error\n");
	}
	
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if( pid > 0)
	{
		sleep(1);
		//It's interesting that let child go first 
		//and I found that the read from pipe  would wait for pipe input finished

		close(fd[0]);
		write(fd[1],"hello world!\n",13);
		waitpid(-1,NULL,0);//It's neccessary to wait for child to terminate.
	}
	else
	{
		close(fd[1]);
		n = read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO,line,n);
	}

	return 0;
}
