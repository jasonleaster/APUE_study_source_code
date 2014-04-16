#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN	128
#define TIMEOUT 20

void sigalrm(int signo)
{
}

void print_uptime(int sockfd,struct addrinfo *aip)
{
	int n;
	char buf[BUFLEN];
	
	buf[0] = 0;
	if(sendto(sockfd,buf,1,0,aip->ai_addr,aip->ai_addrlen) < 0)
	{
		printf("sendto error\n");
		return 0;
	}

	alarm(TIMEOUT);
	
	if((n = recvfrom(sockfd,buf,BUFLEN,0,NULL,NULL)) < 0)
	{
		if(errno != EINTR)
		{
			alarm(0);
			printf("recv error\n");
		}
	}

	alarm(0);
	
	write(STDOUT_FILENO,buf,n);
}

int main(int argc,char* argv[])
{
	struct addrinfo *aip,*ailist;
	struct addrinfo hint;
	int sockfd,err;
	struct sigaction sa;

	if(argc != 2)
	{
		printf("usage : ruptime hostname\n");
		return 0;
	}
	
	sa.sa_handler = sigalrm;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	if(sigaction(SIGALRM,&sa,NULL) < 0)
	{
		printf("sigaction error\n");
	}

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	if((err = getaddrinfo(argv[1],"ruptime",&hint,&ailist)) != 0)
	{
		printf("getaddrinfo error\n");
	}

	for(aip = ailist;aip != NULL;aip = aip->ai_next)
	{
		if((sockfd = socket(aip->ai_family,SOCK_DGRAM,0)) < 0)
		{
			err = errno;
		}
		else
		{
			print_uptime(sockfd,aip);
			return 0;
		}
	}

	fprintf(stderr,"can't contact %s : %s\n",argv[1],strerror(err));

	return 1;
}

