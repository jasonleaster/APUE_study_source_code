#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096

static void sig_pipe(int);

int s_pipe(int fd[2]);

int main()
{
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	struct sigaction sa;
	
	sa.sa_handler = sig_pipe;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if(sigaction(SIGPIPE,&sa,NULL) < 0)
	{
		printf("sigaction error\n");
	}

	if(s_pipe(fd) < 0)
	{
		printf("pipe error\n");
	}

	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid > 0)
	{
		close(fd[1]);

		sleep(1);	
	
		while(fgets(line,MAXLINE,stdin) !=  NULL)
		{
			int temp = 0;
			n = strlen(line);
			if((temp = write(fd[0],line,n)) != n)
			{
				printf("write error to pipe\n");
			}

			printf("temp = %d\n",temp);

			if((n = read(fd[0],line,MAXLINE)) < 0)
			{
				printf("read error\n");
			}

			if(n == 0)
			{
				printf("child close pipe\n");
				break;
			}
	
			line[n] = 0;
			if(fputs(line,stdout) == EOF)
			{
				printf("fputs error\n");
			}
		}
		
		if(ferror(stdin))
		{
			printf("fgets error on stdin\n");
		}
		
		return 0;
	}
	else
	{
		close(fd[0]);
		
		if(fd[1] != STDIN_FILENO && dup2(fd[1],STDIN_FILENO) != STDIN_FILENO)
		{
			printf("dup2 error to stdin\n");
		}

		if(fd[1] != STDOUT_FILENO && dup2(fd[1],STDOUT_FILENO) != STDOUT_FILENO)
		{
			printf("dup2 error to stdout\n");
		}

		if(execl("./add2","add2",NULL) < 0)
		{
			printf("execl error\n");
		}

		return 0;
	}
}

static void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

int s_pipe(int fd[2])
{
	return pipe(fd);
}
