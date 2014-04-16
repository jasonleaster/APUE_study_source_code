#include <apue.h>
#include <fcntl.h>

pid_t
lock_test(int fd,int type,off_t offset,int whence,off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	locl.l_len = len;

	if(fcntl(fd,F_GETLK,&lock) < 0)
	{
		err_sys("fcntl error\n");
	}

	if(lock.l_type == F_UNLCK)
	{
		return 0;
	}

	return lock.l_pid;
}
