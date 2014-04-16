#include "apue.h"
#include "stdio.h"
#include <fcntl.h>
#include "myerr.h"

int main()
{
	if(open("./test.txt",O_RDWR) < 0)
	{
		err_sys("open error");
	}
	if(unlink("./test.txt") < 0)
	{
		err_sys("unlink error");
	}
	printf("file unlinked");
	sleep(15);
	printf("done\n");

	return 0;	
}
