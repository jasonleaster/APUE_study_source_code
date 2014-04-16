#include"apue.h"
#include"unistd.h"
#include"fcntl.h"
int main()
{
	int file_descriptor = 0;
	int duped_fd = 0;
	if((file_descriptor = open("./text.t",O_RDONLY)) < 0)
	{
		printf("open error\nprocess end\n");
		return 0;
	}
	else
	{
		duped_fd = dup(file_descriptor);
		printf("The duped file descriptor is %d\n",duped_fd);
		printf("The file_descritor before dup:%d\n",file_descriptor);
	}
	return 0;
}
