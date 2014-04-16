#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	time_t buffer[BUFSIZ];
	struct tm* p_tm = NULL;
	
	time(buffer);
	
	if((p_tm = (struct tm*)malloc(sizeof(struct tm))) == NULL)
	{
		printf("malloc error\nprocess end\n");
		return 0;
	}	
	
	mktime(p_tm);

	printf("%s\n",asctime(p_tm));

	printf("%s\n",ctime(buffer));

	free(p_tm);
	return 0;
}
