#include "apue.h"
#include "stdio.h"
#include "myerr.h"
#include "/Ad_Pro_in_Unix/chapter_2/path_alloc.c"

int main()
{	
	char *ptr;
	size_t size;

	if(chdir("/usr/") < 0)
	{
		err_sys("chdir failed\n");
	}
	
	ptr = path_alloc(&size);
	
	if(getcwd(ptr,size) == NULL)
	{
		err_sys("getcwd failed\n");
	}
	
	printf("pwd = %s\n",ptr);

	return 0;
}
