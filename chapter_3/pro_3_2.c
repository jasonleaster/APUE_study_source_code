/*******************************************************************
code writer: liuzijian
time : 2013.12.30
code switch:
If you want to get the file.hole ,just use the firtst program 
If you want to get the file.nohole,please use the second program
********************************************************************/

/**********   This program for fiel.hole   ************************/
/*
#include"apue.h"
#include"fcntl.h"
#include"myerr.h"
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
	int fd;
	if ((fd = creat("file.hole",FILE_MODE)) < 0)
	{
		err_sys("creat error");
	}
	if (write(fd,buf1,10) != 10)
	{
		err_sys("buf1 write error");
	}	
	if(lseek(fd,16384,SEEK_SET) == -1)
	{
		err_sys("lseek error");
	}
	if(write(fd,buf2,10) != 10)
	{
		err_sys("buf2 write error");
	}
	exit(0);
}
*/
/**********   This program for fiel.nohole   ************************/

#include"apue.h"
#include"fcntl.h"
#include"myerr.h"
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
	int fd;
	if ((fd = creat("file.nohole",FILE_MODE)) < 0)
	{
		err_sys("creat error");
	}
	if (write(fd,buf1,10) != 10)
	{
		err_sys("buf1 write error");
	}
	
	//if(lseek(fd,16384,SEEK_SET) == -1)
	//{
	//	err_sys("lseek error");
	//}
	if(write(fd,buf2,10) != 10)
	{
		err_sys("buf2 write error");
	}
	exit(0);
}

