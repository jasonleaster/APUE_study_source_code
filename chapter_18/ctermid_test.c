#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	char name[4096];

	printf("The return string of ctermid when parameter is name:%s\n",ctermid(name));
	
	printf("The return string of ctermid when parameter is NULL:%s\n",ctermid(NULL));

	return 0;
}
