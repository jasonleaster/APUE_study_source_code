#include<stdio.h>
int main()
{
	int i = 0;
	int a[100];
	memset(a,0,sizeof(a));
	for(i = 0;i < 100;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}
