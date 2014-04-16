#include "apue.h"
#include "stdio.h"
#include "myerr.h"

#define _BSD_SOURCE

#include "sys/sysmacros.h"
#include "/usr/include/x86_64-linux-gnu/sys/types.h"

#ifdef SOLARIS
	#include <sys/mkdev.h>
#endif

int main(int argc,char* argv[])
{
	int i;
	struct stat buf;
	
	for(i = 0;i < argc;i++)
	{
		printf("%s\n",argv[i]);
		if(stat(argv[i],&buf) < 0)
		{
			err_ret("stat error\n");
			continue ;
		}
	
		printf("dev = %d/%d",major(buf.st_dev),minor(buf.st_dev));
		if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		{
			printf("(%s) rdev = %d/%d",(S_ISCHR(buf.st_mode)) ? "character":"block",major(buf.st_rdev),minor(buf.st_rdev));
		}
			
		printf("\n");
	}

	return 0;
}
