#include<stdio.h>
#include<string.h>
#include <wchar.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main()
{
	int temp = 0;
	char character = 10;
	wchar_t array[ARRAY_SIZE];

	wmemset(array,11,sizeof(wchar_t)*ARRAY_SIZE);

	for(temp = 0;temp < ARRAY_SIZE-1 ; temp++)
	{
		printf("hello\n");
		printf("number%d :%d\n",temp,array[temp]);
		printf("world\n");
	}

	return 0;	
}

