#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc,char* argv[])
{
	int 	fdin,fdout;
	void	*src,*dst;
	struct stat	statbuf;
	
	if(argc != 3)
	{
		printf("usage: %s <fromfile> <tofile>",argv[0],);
		return 0;
	}

	if((fdin = open(argv[1],O_RDONLY)) < 0)
	{
		printf("can't open %s for reading\n",argv[1]);
		return 0;
	}

	if((fdout = open(argv[2],O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR)) < 0)
	{
		printf("can't create %s for writing\n",argv[2]);
		return 0;
	}

	if(fstat(fdin,&statbuf) < 0)
	{
		printf("fstat error\n");
	}

	if(lseek(fdout,statbuf.st_size-1,SEEK_SET) == -1)
	{
		printf("lseek error\n");
	}

	if(write(fdout,"",1) != 1)
	{
		printf("write error\n");
	}

	if((src = mmap(0,statbuf.st_size,PROT_READ,MAP_SHARED,fdin,0)) == MAP_FAILED)
	{
		printf("mmap error for input\n");
	}

	if((dst = mmap(0,statbuf.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fdout,0)) == MAP_FAILED)
	{
		printf("mmap error for input\n");
	}
	memcpy(dst,src,statbuf.st_size);

	return 0;
}
