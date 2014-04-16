#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("the user login: %s\n",getlogin());
	return 0;
}
