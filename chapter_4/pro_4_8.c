#include<apue.h>
#include<fcntl.h>
#include<myerr.h>
int main(int argc ,char* argv[])
{
	int file_descriptor = 0;

	if(argc != 2)
	{
		err_quit("usage : a.out <pathname>");
	}
	
	if(access(argv[1],R_OK) < 0)
	{
		err_ret("access error for %s",argv[1]);
	}
	else
	{
		printf("read access OK\n");
	}

	if(file_descriptor = open(argv[1],O_RDONLY) < 0)
	{
		err_ret("open error for %s",argv[1]);
	}
	else
	{
		printf("open for reading OK\n");
	}

	close(file_descriptor);

	return 0;
}
