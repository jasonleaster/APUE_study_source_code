#include <apue.h>
#include <signal.h>

int main()
{
	sigset_t hehe;

	printf("return value of sigemptyset :%x\n",sigemptyset(&hehe));

	printf("return value of sigefillset :%x\n",sigfillset(&hehe));

	printf("now we insert the (SIGINT)\n");
	
	printf("return value of sigeaddset :%d\n",sigaddset(&hehe,SIGCLD));
	return 0;
}
