#include <limits.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	struct devdir *ddp;
	struct stat    fdstat;
	char *rval;
	
	if(fstat(STDIN_FILENO,&fdstat) < 0)
	{
		printf("fstat error\n");
	}

	if(fstat(STDIN_FILENO,&fdstat) < 0)
	{
		printf("fstat error\n");
	}

	rval = searchdir("/dev",NULL);

	return 0;
}
