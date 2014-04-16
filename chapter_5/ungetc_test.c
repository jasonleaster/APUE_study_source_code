/********************************************************
code writer : EOF
code date : 2014.03.25
e-mail : jasonleaster@gmail.com

***********************************************************/
#include "stdio.h"
int main()
{
	int counter = 0;
	int character = 0;
	int temp = 0;
	while((character = getchar()) != EOF)
	{
		counter++;
		if(counter == 3)
		{
			if(ungetc(character,stdin) == EOF)
			{
				printf("ungetc error\n");
			}
			else
			{
				temp = character;
			}
		}

		if(counter == 4)
		{
			if(character == temp)
			{
				printf("\nungec success\n");
				putchar(character);
				printf("\n");
				continue;
			}	
		}
		
		putchar(character);
		
	}

	return 0;
}
