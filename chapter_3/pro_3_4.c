#include"apue.h"
#include"stdio.h"
#include"myerr.h"
#define BUFFSIZE 4096
int main()
{
	int n = 0;
	int m = 0;
	char buf[BUFFSIZE] ;
	
	while((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0 )
	{
		printf("sucess to read %d byte from the stdin\n",n);
		if((m = write(STDOUT_FILENO,buf,n)) != n)
		{
			err_sys("write error");
		}
		else
		{		
			printf("sucess to write %d byte to the stdout\n",m);
		}
	}
	if(n < 0 )
	{
		err_sys("read error");
	}
	exit(0);
}

