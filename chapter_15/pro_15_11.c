#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

#define	PAGER	"${PAGER:-more}"
#define MAXLINE 4096

int main(int argc,char* argv[])
{
	char 	line[MAXLINE];
	FILE	*fpin,*fpout;
	
	if(argc != 2)
	{
		printf("usage: a.out <pathname>\n");
	}

	if((fpin = fopen(argv[1],"r")) == NULL)
	{
		printf("fopen error\n");
	}

	if((fpout = popen(PAGER,"w")) == NULL)//single direction pipe
	{
		printf("popen error\n");
	}

	while(fgets(line,MAXLINE,fpin) != NULL)
	{
		if(fputs(line,fpout) == EOF)
		{
			printf("fputs error to pipe");
		}
	}

	if(ferror(fpin))
	{
		printf("fgets error\n");
	}

	if(pclose(fpout) == -1)
	{
		printf("pclose error\n");
	}

	return 0;
}
