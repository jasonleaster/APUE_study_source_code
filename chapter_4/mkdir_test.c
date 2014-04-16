#include "apue.h"
#include "stdio.h"

int main()
{
	if(mkdir("./a_dir_made_from_mkdir",S_IRUSR|S_IWUSR|S_IXUSR) < 0)
	{
		printf("mkdir error\n");
	}
	
	return 0;
}
