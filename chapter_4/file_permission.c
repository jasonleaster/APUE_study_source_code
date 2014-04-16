/********************************************************************************
code writer: liuzijian

date:2014.01.01

just test the file permission
**********************************************************************************/
#include"apue.h"
#include"fcntl.h"
#include"stdio.h"
int main(int argc,char* argv[])
{
	if(argc != 2)
	{
		printf("parameter error!\n");
	}
	
	if(access(argv[1],R_OK) < 0)
	{
		printf("read %s denied!\n",argv[1]);
	}
	else
	{
		printf("read %s access OK!\n",argv[1]);
	}
	
	if(access(argv[1],W_OK) < 0)
	{
		printf("write %s denied!\n",argv[1]);
	}
	else
	{
		printf("write %s access OK!\n",argv[1]);
	}

	if(access(argv[1],X_OK) < 0)
	{
		printf("execute %s denied!\n",argv[1]);
	}
	else
	{
		printf("execute %s access OK!\n",argv[1]);
	}

	if(access(argv[1],F_OK) < 0)
	{
		printf("file %s does not exist!\n",argv[1]);
	}
	else
	{
		printf("file %s is existed!\n",argv[1]);
	}
	
	return 0;	
}
