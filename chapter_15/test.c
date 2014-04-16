#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE	4096

static void sig_pipe(int signo)
{
	printf("SIGPIPE	caught\n");
}

int main()
{
	int n,fd1[2],fd2[2];
	pid_t	pid;
	char line[MAXLINE];
	
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_pipe;
	sigaddset(&sa.sa_mask,SIGPIPE);
	
	if(sigaction(SIGPIPE,&sa,NULL) < 0)
	{
		printf("sigaction error\n");
		return 0;
	}

	if(pipe(fd2) < 0 || pipe(fd1) < 0)
	{
		printf("pipe error\n");
		return 0;
	}

	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);

		while(fgets(line,MAXLINE,stdin) != NULL)
		{
			n = strlen(line);
			if(write(fd1[1],line,n) != n)
			{
				printf("write error\n");
			}

			if(read(fd2[0],line,MAXLINE) < 0)//Is there some problems that we use the same buffer--line
			{
				printf("read error from pipe\n");
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
			printf("fgets error\n");
		}
		
/*		if(waitpid(pid,NULL,0) < 0)
		{
			printf("waitpid error\n");
		}
*/
		return 0;
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);

		if(fd1[0] != STDIN_FILENO)
		{
			if(dup2(fd1[0],STDIN_FILENO) != STDIN_FILENO)
			{
				printf("dup2 error to stdin\n");
			}
			
			close(fd1[0]);
		}

		if(fd2[1] != STDOUT_FILENO)
		{
			if(dup2(fd2[1],STDOUT_FILENO) != STDOUT_FILENO)
			{
				printf("dup2 error\n");
			}
			close(fd2[1]);
		}
		pause();
/*		if(waitpid(getppid(),NULL,0) < 0)
		{
			printf("waitpid error\n");
		}
		if(execl("./add2","add2",NULL) < 0)
		{
			printf("execl error\n");
		}
*/
	}

	return 0;

}
