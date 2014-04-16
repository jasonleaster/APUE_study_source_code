#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define	MAXLINE	4096

int main()
{
	char line[MAXLINE];
	FILE*	fpin;

//	execl("SHELL","sh","-c","./myuclc",NULL);
	
	if((fpin = popen("./myuclc","r")) == NULL)
	{
		printf("popen error\n");
	}

	for(;;)
	{
		fputs("prompt >",stdout);
		fflush(stdout);

		if(fgets(line,MAXLINE,fpin) == NULL)
		{
			break;
		}

		if(fputs(line,stdout) == EOF)
		{
			printf("fputs error to pipe\n");
		}
	}

	if(pclose(fpin) == -1)
	{
		printf("pclose error\n");
	}

	putchar('\n');

	return 0;
}
