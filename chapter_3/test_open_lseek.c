#include"apeu.h"
#include"fcntl.h"

int main()
{
	int file_descriptor = 0;
	int writed_character = 0;
	char buf[] = {"hello world!Now I am using write function."};

	if((file_descriptor = open("./text.t",O_RDWR||O_APPEND)) < 0)
	{
		printf("open error\nProcess end\n");
		return 0;
	}
	else
	{
		while(writed_character>=0)
		{
		
			if((writed_character = write(file_descriptor,buf,10))!= 10)
			{
				printf("write error\n");
			}
		}
		
	}
	return 0;
}
