/***************
just a demo
***************/
#include"apue.h"
#include"fcntl.h"
#include"stdio.h"

int main()
{
	int file_descriptor = 0;

	if(file_descriptor = open("./text.t",O_RDONLY) < 0)
	{
		printf("open error\nprocess end\n");
		return 0;
	}
	else
	{
		printf("open success\n");
		close(file_descriptor);//if there is not close function ,it would be OK...
	}
	return 0;
}
