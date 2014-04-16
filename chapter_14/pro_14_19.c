#include <stdio.h>
#include <stropts.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main()
{
	int	n,flags;
	char 	ctlbuf[BUFFSIZ],datbuf[BUFFSIZ];
	struct strbuf	ctl,dat;

	ctl.buf = ctlbuf;
	ctl.maxlen = BUFFSIZE;
	dat.buf = datbuf;
	dat.maxlen = BUFFSIZE;

	for(;;)
	{
		flag = 0;
		
		if((n = getmsg(STDIN_FILENO,&ctl,&dat,)) < 0)
		{
			printf("getmsg error\n");
		}

		fprintf(stderr,"flag = %d,ctl.len = %d,dat.len = %d\n",flag,ctl.len,dat.len);
	
		if(dat.len == 0)
		{
			return 0;
		}
		else if (dat.len > 0)
		{
			if(write(STDOUT_FILENO,dat.buf,dat.len) < 0)
			{
				printf("write error\n");
			}
		}
	}

	return 0;
}
