#include"apue.h"
#include"myerr.h"
int main()
{
	printf("uid = %d,gid = %d\n",geruid(),getgid());
	exit(0);
}
