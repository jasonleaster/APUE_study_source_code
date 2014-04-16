#include <pwd.h>
#include <stdio.h>

int main()
{
	struct passwd* p_passwd =  NULL;
	
	p_passwd = getpwnam("liuzjian");

	printf("the user name:%s\n",p_passwd->pw_name);
	printf("the numberical user ID:%u\n",p_passwd->pw_uid);
	printf("the numberical group ID:%u\n",p_passwd->pw_gid);
	printf("the comment field:%s\n",p_passwd->pw_gecos);
	printf("the initial working directory:%s\n",p_passwd->pw_dir);
	printf("the initial shell:%s\n",p_passwd->pw_shell);
/*	printf("the user access class:%s\n",p_passwd->pw_class);
	printf("the next time to change password:%d\n",p_passwd->pw_change);
	printf("the account expiration time:%d\n",p_passwd->pw_expire);
*/	return 0;
}
