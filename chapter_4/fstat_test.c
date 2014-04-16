#include "apue.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdio.h"

int main()
{
	struct stat buf;
 
	int file_descriptor = 0;

	if((file_descriptor = open("./test.txt",O_RDWR)) < 0)
	{
		printf("open error\n");
	}
	
	if(fstat(file_descriptor,&buf) < 0)
	{
		printf("fstat error\n");
	}
	
	printf("The file mode     is : %ld\n",buf.st_mode);
	printf("The i-node number is : %ld\n",buf.st_ino);
	printf("The device number is : %ld\n",buf.st_dev);
	printf("The device number for special files is : %d\n",buf.st_rdev);
	printf("The number of links   is : %ld\n",buf.st_nlink);
	printf("The user ID of owner  is : %ld\n",buf.st_uid);
	printf("The group ID of owner is : %ld\n",buf.st_gid);
	printf("The size in bytes  for regular files is : %ld\n",buf.st_size);
	printf("The best I/O size is : %ld\n",buf.st_blksize);
	printf("The number of disk blocks allocated is : %ld\n",buf.st_blocks);
	
	return 0;
}
