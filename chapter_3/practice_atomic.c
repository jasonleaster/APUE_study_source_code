/*******************************************************
Code writer:EOF
Code date: 2014.02.05

Code purpose:
	Read some characters from the standard input
and then write them into the end of  file"text.t"

Touch me: if this code somewhere is not very well,please touch me
e-mail:jasonleaster@gmail.com
*******************************************************/
#include"apue.h"
#include"unistd.h"
#include"fcntl.h"

#define BUFFSIZE 4096

int main()
{
	int file_descriptor = 0;
	int bytes = 0;	
	off_t off_set = 0;
	char buf[BUFFSIZE];
	

	if((file_descriptor = open("./text.t",O_RDWR,O_APPEND)) < 0)
	{
		printf("open error\nprocess end\n");
		return 0;
	}
	else
	{
		//while((bytes = pread(STDIN_FILENO,buf,BUFFSIZE-1,SEEK_CUR) >= 0))
		while((bytes = read(STDIN_FILENO,buf,BUFFSIZE-1)) > 0)
		{
			if((off_set = lseek(file_descriptor,0,SEEK_END)) < 0)
			{
				printf("lseek error\n");
			}
	
		//	if(write(file_descriptor,buf,bytes) != bytes)
			if(pwrite(file_descriptor,buf,bytes,off_set) != bytes)
			{
				printf("pwrite error\nprocess end\n");
				return 0;
			}
		}
	}
	
	exit(0);
}
