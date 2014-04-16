#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include </Ad_Pro_in_Unix/chapter_16/pro_16_9.c>
#include <sys/socket.h>

#define MAXADDRLEN	256
#define BUFLEN		128

extern int connect_retry(int,const struct sockaddr* socklen,socklen_t);

void print_uptime(int sockfd)
{
	int n;
	char buf[BUFLEN];

	while((n = recv(sockfd,buf,BUFLEN,0)) > 0)
	{
		write(STDOUT_FILENO,buf,n);
	}

	if(n < 0)
	{
		printf("recv error\n");
	}
}

int main(int argc,char* argv[])
{
	struct addrinfo * ailist,* aip;
	struct addrinfo hint;
	
	int sockfd,err;

	if(argc != 2)
	{
		printf("usage: ruptime hostname\n");
		return 0;
	}

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = 0;
	hint.ai_protocol = 0;
	hint.ai_addrlen  = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	
	if((err = getaddrinfo(argv[1],"time",&hint,&ailist)) != 0)
	{
		printf("getaddrinfo error %s\n",gai_strerror(err));
	}

	for(aip = ailist;aip != NULL;aip = aip->ai_next)
	{
		if((sockfd = socket(aip->ai_family,SOCK_STREAM,0)) < 0)
		{
			err = errno;
		}

		if(connect_retry(sockfd,aip->ai_addr,aip->ai_addrlen) < 0)
		{
			err = errno;
		}
		else
		{
			print_uptime(sockfd);
			return 0;
		}
	}
	
	fprintf(stderr,"can't connect to %s: %s\n",argv[1],strerror(err));

	return 0;
}
