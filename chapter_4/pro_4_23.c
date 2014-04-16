#include "apue.h"
#include "unistd.h"
#include "myerr.h"

int main()
{
	if(chdir("/tmp") < 0)
	{
		err_sys("chdir failed\n");
	}
	
	printf("chdir to /tmp succeeded\n");

	return 0;
}
