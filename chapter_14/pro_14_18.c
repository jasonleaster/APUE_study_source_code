#include <fcntl.h>
#include <stropts.h>
#include <stdio.h>
//#include <sys/conf.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	int	fd,i,nmods;
	struct str_list	list;
	
	if(argc != 2)
	{
		printf("usage: %s <pathname>",argv[0]);
		return 0;
	}

	if((fd = open(argv[1],O_RDONLY)) < 0)
	{
		printf("can't open %s\n",argv[1]);
		return 0;
	}

	if(isastream(fd) == 0)
	{
		printf("%s is not a streams\n",argv[1]);
		return 0;
	}

	if(nmods = ioctl(fd,I_LIST,(void*) 0) < 0)
	{
		printf("I_LIST error for nmods\n");
		return 0;
	}

	printf("#modules = %d\n",nmods);

	list.sl_modlist == (struct str_mlist*)calloc(nmods,sizeof(struct str_mlist));
	if(list.sl_modlist == NULL)
	{
		printf("calloc error\n");
		return 0;
	}
	list.sl_nmods = nmods;

	if(ioctl(fd,I_LIST,&list) < 0)
	{
		printf("I_LIST error for list\n");
	}

	for(i = 1;i <= nmods;i++)
	{
		printf("%s: %s\n",(i == nmods) ? "drivers" : "module",list.sl_modlist++->l_name);
	}
	
	return 0;
}
