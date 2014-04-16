#include <stdio.h>
#include <shadow.h>

int main()
{
	struct spwd* p_spwd = NULL;

	if((p_spwd = getspnam("liuzjian")) == NULL)
	{
		printf("getspnam error\n");
	}
	
	printf("user login name :%s\n",p_spwd->sp_namp);
	printf("encrypted password: %s\n",p_spwd->sp_pwdp);
	printf("day since Epoch of last password change :%ld\n",p_spwd->sp_lstchg);
	printf("days until change allowed :%ld\n",p_spwd->sp_min);
	printf("days before change required:%ld\n",p_spwd->sp_max);
	printf("days warning for expiration:%ld\n",p_spwd->sp_warn);
	printf("days before account inactive:%ld\n",p_spwd->sp_inact);
	printf("days since Epoch when account expires:%ld\n",p_spwd->sp_expire);
	printf("reserved :%lu\n",p_spwd->sp_flag);

	return 0;
}
