#include <stdio.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN     128
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX

	#define HOST_NAME_MAX 256

#endif

extern int initserver(int,struct sockaddr* ,socklen_t,int);

void serve(int sockfd)
{
	int n;
	socklen_t alne;
	FILE *fp;
	char buf[BUFLEN];
	char abuf[MAXADDRLEN];

	for(;;)
	{
		alen = MAXADDRLEN;
		if((n = recvfrom(sockfd,buf,BUFLEN,0,(struct sockaddr*)abuf,&alen)) < 0)
		{
			syslog(LOG_ERR,"ruptimed :recvfrom error :%s\n",strerror(errno));
			return 1;
		}

		if((fp = popen("/usr/bin/uptime","r")) == NULL)
		{
			sprintf(sockfd,"error %s\n",strerror(errno));
			sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)abuf,alen);
		}
		else
		{
			if(fgets(buf,BUFLEN,fp) != NULL)
			{
				sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)abuf,alen);
			}
			
			pclose(fp);
		}

	}
}

int main(int argc,char * argv[])
{
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int 		sockfd,err,n;
	char 		*host;

	if(argc != 2)
	{
		printf("usage : ruptimed\n");
		return 0;
	}

#ifdef _SC_HOST_NAME_MAX

	n = sysconf(_SC_HOST_NAME_MAX);
	if(n < 0)

#endif
	   n = HOST_NAME_MAX;
	host = malloc(n);

	if(host == NULL)
	{
		printf("malloc error\n");
		return 0;
	}

	if(gethostname(host,n) < 0)
	{
		printf("gethostname error\n");
	}

	daemonize("ruptimed");

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_next  = NULL;
	hint.ai_addr  = NULL;

	if((err = getaddrinfo(host,"ruptime",&hint,&ailist)) != 0)
	{
		syslog(LOG_ERR,"ruptime : getaddrinfo error:%s",gai_strerror(err));
		return 0;
	}

	for(aip = ailist; aip != NULL;aip = aip->ai_next)
	{
		if((sockfd = initserver(SOCK_DGRAM,aip->ai_addr,aip->ai_addrlen,0)) >= 0)
		{
			serve(sockfd);
			return 0;
		}
	}

	return 1;
}
