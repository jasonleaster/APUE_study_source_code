#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define NLOOPS	1000
#define SIZE	sizeof(long)

static int update(long * ptr)
{
	return (*ptr)++;
}

int main()
{
	int fd,i,counter;
	pid_t	pid;
	void * area;
	int fd1[2],fd2[2];

/*	if((fd = open("/dev/zero",O_RDWR)) < 0)
	{
		printf("open error\n");
	}
*/
	if((area = mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANON,-1,0)) == MAP_FAILED)
	{
		printf("mmap error\n");
	}

//	close(fd);

	if(pipe(fd1) < 0 || pipe(fd2) < 0)
	{
		printf("pipe error\n");
	}

	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(pid > 0)
	{
	
		close(fd1[0]);
		close(fd2[1]);
		
		int c;
		
		for(i = 0;i < NLOOPS;i++)
		{
			if((counter = update((long*) area)) != i)
			{
				printf("parent: expect %d,got %d\n",i,counter);
			}

//			TELL_CHILD(pid);
			if(write(fd1[1],"p",1) != 1)
			{
				printf("write error\n");
			}

//			WAIT_CHILD();
			if(read(fd2[0],&c,1) != 1)
			{
				printf("read error\n");
			}
		}
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		
		for(i = 0;i < NLOOPS;i++)
		{
			if((counter = update((long*) area)) != i)
			{
				printf("parent: expect %d,got %d\n",i,counter);
			}
			
//			TELL_PARENT();
			if(write(fd2[1],"c",1) != 1)
			{
				printf("write error\n");
			}
		}
	}

	return 0;
}

