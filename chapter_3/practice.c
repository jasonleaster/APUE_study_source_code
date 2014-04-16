/***************************************************************************
code writer :EOF

date :2013.12.31

This program is coded for practice in 'open' 'write' 
*********************************************************************************/
#include"apue.h"
#include"stdio.h"
#include"myerr.h"
#include"fcntl.h"
#include"unistd.h"

#define BUFFSIZE 4096

int main()
{
	int val = 0;
	int number = 0;
	int temp = 0;
	int bagman = 0;
	int num = 0;
	char buf[BUFFSIZE] = {'\0'};

	if((val = open("/hellomod/hello.c",O_RDWR)) > 0 )
	{
		printf("val = %d\nopen successful!\n",val);
		
		while((number = read(val,buf,BUFFSIZE)) > 0 )
		{	
			if((temp = write(STDIN_FILENO,buf,BUFFSIZE)) != BUFFSIZE)
			{
				err_sys("write wrong!\n");
			}
			else
			{	
				printf("%d bytes have been writed into stdout\n",number);
			}	
		
		}	

		if((number = creat("./notebook",FILE_MODE)) > 0)
		{	
			printf("file %d creat successful!\n",number);
			
			if((num = open("./notebook",O_RDWR)) > 0 )
			{
				printf("file %d open successful!\n",num);
				if(lseek(val,0,SEEK_SET) == -1)
				{
					err_sys("cannot seek\n");
				}
				else
				{
					printf("seek ok\n");
				}

				while((temp = read(val,buf,BUFFSIZE)) >0 )
				{
					if( (bagman = write(num,buf,BUFFSIZE) ) != BUFFSIZE )
					{	
						err_sys("write wrong!\n");
					}
					else
					{
			 			printf("%d bytes have been writed into file",bagman);
					}	
				}	
			}
			else
			{
				err_sys("open error!\n");
			}
			
		}
		else
		{
			err_sys("creat error!\n");
		}
	}	

	if(val < 0)
	{
		err_sys("open error\n");
	}

	if(close(val) != 0)
	{
		err_sys("close error\n");
	}
	else
	{
		printf("close file sucessful!\n");
	}
	return 0;	
}
