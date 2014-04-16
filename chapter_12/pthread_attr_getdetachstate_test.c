#include <stdio.h>
#include <pthread.h>

void* thread_func(void*);

int main()
{
	int temp = 0;
	int err	 = 0;
	int return_val = 0;

	pid_t		pid;
	pthread_t	tid;
	pthread_attr_t	attr;

	pid  = getpid();
	tid = pthread_self();
	printf("current pid :%u\ncurrent thread %u\n",(unsigned int)pid,(unsigned int)tid);
	
	err = pthread_attr_init(&attr);

	if(err != 0)
	{
		return err;
	}	

	err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	if(err == 0)
	{
		err = pthread_create(&tid,NULL,thread_func,0);
	
		if(err != 0)
		{
			printf("can't creat thread\n");
		}
	}
	
	err = pthread_join(tid,NULL);
	
	pthread_attr_destroy(&attr);
	
	return 0;
}

void* thread_func(void* smg)
{
	printf("thread processing\n");
	printf("current thread ID:%u\n",(unsigned int)pthread_self());
	printf("current PID:%u\n",(unsigned int)getpid());
	printf("thread end\n");
	return (void*)1;
}
