#include"apue.h"
#include"myerr.h"
int main()
{
	int c;
	while((c = getc(stdin)) != EOF)
	{
		if(putc(c,stdout) == EOF)
		{
			err_sys("output error\n");
		}
	}
	if(ferror(stdin))
	{
		err_sys("input error\n");
	}
	exit(0);
}

