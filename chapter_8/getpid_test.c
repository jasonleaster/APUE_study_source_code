#include <fcntl.h>
#include <stdio.h>

int main()
{
	printf("current process ID:%d\n",getpid());
	printf("parent  process ID:%d\n",getppid());
	printf("real 	user    ID:%d\n",getuid());
	printf("effective user  ID:%d\n",geteuid());
	printf("real group	ID:%d\n",getgid());
	printf("effective user	ID:%d\n",getegid());
	return 0;
}
