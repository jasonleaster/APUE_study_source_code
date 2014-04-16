#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include </Ad_Pro_in_Unix/chapter_16/pro_16_10.c>

#define BUFLEN 128
#define QLEN   10

#ifndef HOST_NAME_MAX
	#define HOST_NAME_MAX 256
#endif

//extern int initserver(int,struct sockaddr*,socklen_t,int);

void serve(int sockfd)
{
	int clfd;
	FILE *fp;
	char buf[BUFLEN];

	for(;;)
	{
		clfd = accept(sockfd,NULL,NULL);
		if(clfd < 0)
		{
			syslog(LOG_ERR,"ruptime : accept error : %s\n", strerror(errno));
			return ;
		}

		if((fp = popen("/usr/bin/uptime","r")) == NULL)
		{
			sprintf(buf,"error:%s \n",strerror(errno));
			send(clfd,buf,strlen(buf),0);
		}
		else
		{
			while(fgets(buf,BUFLEN,fp) != NULL)
			{
				send(clfd,buf,strlen(buf),0);
				pclose(fp);
			}
			close(clfd);
		}
	}
}

int main(int argc,char* argv[])
{
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int sockfd,err,n;
	char	*host;

	if(argc != 1)
	{
		printf("usage : ruptimed\n");
		return 0;
	}

#ifdef	_SC_HOST_NAME_MAX

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
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	
	if((err = getaddrinfo(host,"ruptimed",&hint,&ailist)) != 0)
	{
		syslog(LOG_ERR,"ruptimed: getaddrinfo error :%s",gai_strerror(err));
		return 1;
	}

	for(aip = ailist;aip != NULL;aip = aip->ai_next)
	{
		if(sockfd = initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN) >= 0)
		{
			serve(sockfd);
			return 0;
		}
	}

	return 1;
}
