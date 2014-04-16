#include<stdio.h>
int main()
{	
	char* wakaka;
	int  number = 23;
	float* pointer;  
	char houhou = 'Q';
	int* foo;
	float geek = 3.14;
	
	wakaka = &houhou;
	foo = &number;
	pointer = &geek;
	
	printf("wakaka is %d,*wakaka is %c\n\n",wakaka,*wakaka);
	printf("*foo is %d,foo is %d\n\n",*foo,foo);
	printf("pointer is %d,*pointer is %f\n\n",pointer,*pointer);

	return 0;
}
