#include <stdio.h>
#include <grp.h>

int main()
{
	struct group* p_group = NULL;
	
	if((p_group = getgrnam("liuzjian")) == NULL)
	{
		printf("getgrnam error\n");
	}
	
	printf("group name :%s\n",p_group->gr_name);
	printf("encrypted passwd:%s\n",p_group->gr_passwd);
	printf("numberical group ID:%d\n",p_group->gr_gid);
	printf("array of pointers of individual user names :%s\n",*(p_group->gr_mem));

	return 0;
}
