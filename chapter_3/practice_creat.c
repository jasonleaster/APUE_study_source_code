#include<apue.h>
#include<fcntl.h>

#define RWX  (S_IRUSR | S_IWUSR | S_IXUSR)

int main()
{
	int file_descriptor = 0;
	
	if((file_descriptor = creat("./hello.t",RWX)) < 0)
	{
		printf("creat fail\nprocess end");
		return 0;
	}
	else
	{
		printf("creat successful\n");
	}
	
	close(file_descriptor);
	return 0;
}
