#include <stdio.h>
#include </Ad_Pro_in_Unix/chapter_18/pro_18_17.c>

int main()
{
	char *ptr;
	
	if((ptr = getpass("Enter password:")) == NULL)
	{
		printf("getpass error\n");
	}

	printf("password:%s\n",ptr);
	
	while(*ptr != 0)
	{
		*ptr++ = 0;
	}

	return 0;
}
