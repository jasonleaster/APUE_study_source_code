/*******************************************************************************

code writer:liuzijian

date : 2014.01.01

just test what is in the structure -- stat

There would be some warnings during the code is complied,but it doesn't matter.

Just ran the program that you complied is OK!
********************************************************************************/
#include<apue.h>
#include<stdio.h>
int main(int argc,char* argv[])
{
	struct stat buf;
	
	printf("please enter two parameter!\n");
	
	if(argc != 2)
	{
		printf("parameter is wrong!\nplease enter two parameter!\n");
		return 0;
	}
	else
	{
		if(lstat(argv[1],&buf) < 0 )
		{
			printf("lstat is wrong!\n");
		}
		else
		{
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
		}
	}

	return 0;
}
