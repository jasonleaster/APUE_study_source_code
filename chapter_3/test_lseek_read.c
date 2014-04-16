#include"apue.h"
#include"fcntl.h"
#define BUFFSIZE 4096

int main()
{
	int file_descriptor = 0;
	ssize_t readed_character = 0;
	ssize_t writed_character = 0;
	off_t off_set = 0;
	char buf[BUFFSIZE] = {"liuzijian"};
	//size_t read_onece = 100;
 
	if((file_descriptor = open("./text.t",O_RDWR||O_APPEND))< 0)
	{
		printf("open error!\nProcess end!\n");
	}

	if((off_set = lseek(file_descriptor,2,SEEK_SET)) < 0)
	{
		printf("lseek error\n");
	}
	else
	{
		/*if((readed_character = read(file_descriptor,buf,BUFFSIZE-1)) < 0)
		{
			printf("read error\n");
		}*/

		/*
		while(readed_character > 0)
		{
			if((readed_character = read(file_descriptor,buf,read_onece) != read_onece) < 0)
			{
				printf("read error\n");
			}
		}*/
		
		if((writed_character = write(file_descriptor,buf,BUFFSIZE-1)) < 0)
		{
			printf("write error\n");
		}
		/*
		while(writed_character > 0)
		{
			if((writed_character = write(STDOUT_FILENO,buf,read_onece)) != read_onece)
			{
				printf("write error\n");
			}
		}*/
	}

	return 0;
}
