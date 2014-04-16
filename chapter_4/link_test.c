#include "apue.h"
#include "stdio.h"
#include "unistd.h"

int main()
{
	if(symlink("./test.txt","./symbolink_to_test") < 0)
	{
		printf("symlink error\n");
	}

	return 0;
}
