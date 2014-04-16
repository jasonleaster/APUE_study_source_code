#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <string.h>
#include </Ad_Pro_in_Unix/chapter_16/pro_16_10.c>
#include </Ad_Pro_in_Unix/chapter_13/pro_13_1.c>


#define QLEN 10

#ifndef HOST_NAME_MAX

	#define HOST_NAME_MAX 256

#endif

//extern int initserver(int,struct sockaddr*,socklen_t,int);

void serve(int sockfd)
{
	int clfd,status;
	pid_t pid;
	
	for(;;)
	{
		clfd = accept(sockfd,NULL,NULL);
		if(clfd < 0)
		{
			syslog(LOG_ERR,"ruptimed:accept error: %s\n",strerror(errno));
			return ;
		}
	
		if((pid = fork()) < 0)
		{
			syslog(LOG_ERR,"ruptimed: fork error %s\n",strerror(errno));
			return ;
		}
		else if(pid == 0)
		{
			if(dup2(clfd,STDOUT_FILENO) != STDOUT_FILENO || dup2(clfd,STDERR_FILENO) != STDERR_FILENO)
			{
				syslog(LOG_ERR,"ruptimed : unexpected error\n");
				return ;
			}
			close(clfd);
			execl("/usr/bin/uptime","uptime",NULL);
			syslog(LOG_ERR,"ruptimed :unexpected return from exec:%s",strerror(errno));
		}
		else
		{
			close(clfd);
			waitpid(pid,&status,0);
		}
	}
}

int main(int argc,char* argv)
{
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int		sockfd,err,n;
	char 		*host;

	if(argc != 1)
	{
		printf("usage: ruptimed\n");
		return 0;
	}

#ifdef _SC_HOST_NAME_MAX

	n = sysconf(_SC_HOST_NAME_MAX);
	if( n < 0)

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
		return 0;
	}

	daemonize("ruptimed");

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	if((err = getaddrinfo(host,"ruptime",&hint,&ailist)) != 0)
	{
		syslog(LOG_ERR,"ruptimed: getaddrinfo error\n",gai_strerror(err));
		return 1;
	}

	for(aip = ailist; aip != NULL; aip = aip->ai_next)
	{
		if((sockfd = initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN)) >= 0)
		{
			serve(sockfd);
			return 0;
		}	
	}

	return 1;
}
