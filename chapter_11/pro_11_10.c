#include "apue.h"
#include <pthread.h>
#include "myerr.h"

struct foo
{
	int f_count;
	pthread_mutex_t	f_lock;
};

struct foo* foo_alloc(void);

void foo_hold(struct foo*fp);

void foo_rele(struct foo*fp);

void *myfunc1(void* ptr);
void *myfunc2(void* ptr);


int a[100];

int main()
{
	int err = 0;

	int thret1,thret2;
	pthread_t thrd1,thrd2;
	struct foo* fp = NULL;

	memset(a,0,sizeof(a));	

	fp = foo_alloc();

	thret1 = pthread_create(&thrd1,NULL,myfunc1,(void *)fp);
	thret2 = pthread_create(&thrd2,NULL,myfunc2,(void *)fp);

	if((err = pthread_join(thrd1,NULL)) != 0)
	{
		printf("join error %s\n",strerror(err));
	}

	if((err = pthread_join(thrd2,NULL)) != 0)
	{
		printf("join error %s\n",strerror(err));
	}

	printf("thret1 = %d\n",thret1);
	printf("thret2 = %d\n",thret2);
	return 0;
}

struct foo* foo_alloc(void)
{
	struct foo* fp;
	
	if((fp = malloc(sizeof(struct foo))) != NULL)
	{
		fp->f_count = 1;
		if(pthread_mutex_init(&fp->f_lock,NULL) != 0)
		{
			free(fp);
			return NULL;
		}
		
		/*continue initialization*/
	}
	return (fp);
}	

void foo_hold(struct foo*fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
//	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo*fp)
{
//	pthread_mutex_lock(&fp->f_lock);
	if(--fp->f_count == 0)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else
	{
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void* myfunc1(void* ptr)
{
	int i;
	struct foo* fp  = (struct foo*) ptr;

	foo_hold(fp);

	printf("msg: thread 1\n");

	for(i = 0;i < 100;i++)
	{
		printf("X");
		a[i] = i;
	}
	printf("\n");
	foo_rele(fp);
}


void* myfunc2(void* ptr)
{
	int i;
	struct foo* fp  = (struct foo*) ptr;

	foo_hold(fp);
	
	printf("msg: thread2\n");
	
	for(i = 0;i< 100;i++)
	{
		printf("%d, ",a[i]);
	}
	printf("\n");
	foo_rele(fp);
}
