#include <stdio.h>
#include <fcntl.h>
#include <stropts.h>

int test(int fd)
{
	return (ioctl(fd,I_CANPUT,0) != -1);
}

int main(int argc,char* argv[])
{
	
	int i,fd;

	for(i = 1;i < argc;i++)
	{
		if((fd = open(argv[i],O_RDONLY)) < 0)
		{
			printf("%s can't open\n",argv[i]);
			continue;
		}

		//if(isastream(fd) == 0)
		if(test(fd) == 0)
		{
			printf("%s not a stream\n",argv[i]);
		}
		else
		{
			printf("%s streams device\n",argv[i]);
		}
	}

	return 0;
}
