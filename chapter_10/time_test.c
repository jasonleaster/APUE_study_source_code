#include <stdio.h>
#include <time.h>
int main()
{
	time_t t;
	int temp = 0;

	t = time(NULL);

	for(temp = 0;temp < 3;)
	{
		if(time(NULL) - t > 1)
		{
			printf("hello world!\n");
			temp++;
			t = time(NULL);
		}
	}
	return 0;
}
