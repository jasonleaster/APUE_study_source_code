#include <stdio.h>
#define ARRAY_SIZE 10

char* my_memset(char* p_int,char character,size_t num);

int main()
{
	int temp = 0;

	char array[ARRAY_SIZE];

	my_memset(array,10,sizeof(char)*ARRAY_SIZE);

	for(temp = 0;temp < ARRAY_SIZE;temp++)
	{
		printf("temp%d:%d\n",temp,array[temp]);
	}

	return 0;
}


char* my_memset(char* p_int,char character,size_t num)
{
	char * wp = p_int;
	
	while(num >= 4)
	{
		wp[0] = character;
		wp[1] = character;
		wp[2] = character;
		wp[3] = character;
		p_int +=4;
		num -= 4;
	}

	if(num > 0)
	{
		wp[0] = character;
		
		if(num > 1)
		{
			wp[1] = character;
			if(num > 2)
			{
				wp[2] = character;
			}
		}
	}
		
	return wp;
}
