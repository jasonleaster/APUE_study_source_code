#include "apue.h"
#include "stdio.h"
#include "unistd.h"

int main()
{
	if(rename("./test.txt","./hehe.txt") < 0)
	{
		printf("rename error\n");
	}

	return 0;
}
