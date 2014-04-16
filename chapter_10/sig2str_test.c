#include <stdio.h>
//#include <bits/siginfo.h>
#include <signal.h>

int main()
{
	char str[200];
	sig2str(SIGCHLD,str);
	printf("%s\n",str);
	return 0;
}
