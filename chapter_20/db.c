#include "apue_db.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>

/*
 *  Internal index file constants.
 *  These are used to construct records in
 *  the index file and data file.
 */

#define IDXLEN_SZ (4)
#define SEP       (':')
#define SPACE     (' ')
#define NEWLINE   ('\n')

/*
** The following definitions are for hash chains and free
** list chan in the index file.
*/

#define PTR_SZ    (6)
#define PTR_MAX   (999999)
#define NHASH_DEF (137)
#define FREE_OFF  (0)
#define HASH_OFF  (PTR_SZ)


#define read_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))


#define un_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))



typedef unsigned long DBHASH;
typedef unsigned long COUNT;

typedef struct
{
	int	idxfd;
	int	datfd;
	char	*idxbuf;
	char	*datbuf;

	char	*name;

	off_t   idxoff;
	size_t  idxlen;

	off_t   datoff;
	size_t  datlen;

	off_t   ptrval;
	off_t   ptroff;
	off_t   chainoff;
	off_t   hashoff;

	DBHASH  nhash;
	COUNT   cnt_delok;
	COUNT   cnt_delerr;
	COUNT   cnt_fetchok;
	COUNT   cnt_fetcherr;
	COUNT   cnt_nextrec;
	COUNT   cnt_stor1;
	COUNT   cnt_stor2;
	COUNT   cnt_stor3;
	COUNT   cnt_stor4;
	COUNT   cnt_storerr;
} DB;


static DB	*_db_alloc(int);
static void	 _db_dodelete(DB * );
static int 	 _db_find_and_lock(DB *, const char *, int);
static int 	 _db_findfree(DB *db, int keylen, int datlen);
static void	 _db_free(DB *);
static DBHASH	 _db_hash(DB *, const char *);
static char	*_db_readdat(DB *);
static off_t	 _db_readidx(DB *, off_t);
static off_t 	 _db_readptr(DB *, off_t);
static void	 _db_writedat(DB *, const char *, off_t, int);
static void	 _db_writeidx(DB *, const char *, off_t, int, off_t);
static void	 _db_writeptr(DB *, off_t, off_t);

int lock_reg(int fd,       int    cmd, int type, 
             off_t offset, int whence, off_t len)
{
	struct flock lock;
	
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	return (fcntl(fd,cmd,&lock));
}

DBHANDLE
db_open(const char *pathname, int oflag, ...)
{

	if(!pathname)
	{
		printf("empty path!\n pathname :%p\n",pathname);
		exit(-1);
	}

	DB	*db  = NULL;
	int	len  = 0;
	int 	mode = 0;
	size_t	i    = 0;
	
	/*
	** These two array is just used as a buffer.
	*/
	char	asciiptr[PTR_SZ + 1] = {0,};
	char	hash[(NHASH_DEF + 1) * PTR_SZ + 2] = {0,};

	struct stat statbuff;
	
	len = strlen(pathname);
	
	if((db = _db_alloc(len)) ==  NULL)
	{
		printf("_db_alloc failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	db->nhash = NHASH_DEF;
	db->hashoff = HASH_OFF;

	strcpy(db->name, pathname);
	strcat(db->name, ".idx");
	
	if(oflag & O_CREAT)
	{
		va_list ap;
		
		va_start(ap,oflag);
		mode = va_arg(ap,int);
		va_end(ap);

		db->idxfd = open(db->name, oflag, mode);
		strcpy(db->name + len, ".dat");
		db->datfd = open(db->name, oflag, mode);
	}
	else
	{
		db->idxfd = open(db->name, oflag);
		strcpy(db->name + len, ".dat");
		db->datfd = open(db->name, oflag);
	}

	if(db->idxfd < 0 || db->datfd < 0)
	{
		_db_free(db);
		return NULL;
	}

	if((oflag & (O_CREAT | O_TRUNC)) == (oflag & O_CREAT | O_TRUNC))
	{
		if(writew_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
		{
			printf("write_lock failed in function %s\n",
							__FUNCTION__);
			exit(-1);
		}

		if(fstat(db->idxfd, &statbuff) < 0)
		{
			printf("fstat failed in function %s()\n",
						        __FUNCTION__);
			exit(-1);
		}

		if(statbuff.st_size == 0)
		{
			sprintf(asciiptr, "%*d", PTR_SZ, 0);
			hash[0] = 0;

			for (i = 0 ; i < NHASH_DEF + 1;i++ )
			{
				strcat(hash, asciiptr);
			}

			strcat(hash,"\n");

			i = strlen(hash);

			if(write(db->idxfd, hash, i) != i)
			{
				printf("write failed in function %s\n",
							__FUNCTION__);

				exit(-1);
			}
		}

		if(un_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
		{
			printf("un_lock failed in function %s\n",
						    __FUNCTION__);
			exit(-1);
		}
		
	}

	db_rewind(db);

	return db;
}

static DB* _db_alloc(int namelen)
{
	if(namelen <= 0)
	{
		printf("ERROR! @namelen must be bigger than 0 !\n");
		exit(-1);
	}

	DB	*db = NULL;

	if((db = calloc(1,sizeof(DB))) == NULL)
	{
		printf("calloc failed in function %s\n",__FUNCTION__);

		exit(-1);
	}

	db->idxfd = db->datfd = -1;

	if((db->name = malloc(namelen + 5)) == NULL)
	{
		printf("malloc failed in function %s()\n",__FUNCTION__);

		exit(-1);
	}

	if((db->idxbuf = malloc(IDXLEN_MAX + 2)) == NULL)
	{
		printf("malloc failed for index buffer in function %s()\n",
							__FUNCTION__);
		exit(-1);
	}

	if((db->datbuf = malloc(DATLEN_MAX + 2)) == NULL)
	{
		printf("malloc failed for data buffer in function %s()\n",
							__FUNCTION__);
		exit(-1);
	}

	return db;
}

void db_close(DBHANDLE h)
{
	_db_free((DB *) h);
}

static void _db_free(DB * db)
{
	if(!db)
	{
		printf("Warning! you are trying to free a NULL pointer\n");
		return;
	}

	if(db->idxfd >= 0)
	{
		close(db->idxfd);
	}

	if(db->datfd >= 0)
	{
		close(db->datfd);
	}

	if(db->idxbuf != NULL)
	{
		free(db->idxbuf);
	}

	if(db->datbuf != NULL)
	{
		free(db->datbuf);
	}

	if(db->name != NULL)
	{
		free(db->name);
	}

	free(db);
}

char *db_fetch(DBHANDLE h, const char *key)
{

	if(!h || !key)
	{
		printf("ERROR!line:%d h :%p, key:%p in function %s\n",
				__LINE__, (void*)h, key, __FUNCTION__);
		exit(-1);
	}

	DB	*db  = h;
	char	*ptr = NULL;

	if(_db_find_and_lock(db,key,0) < 0)
	{
		ptr = NULL;
		db->cnt_fetcherr++;
	}
	else
	{
		ptr = _db_readdat(db);
		db->cnt_fetchok++;
	}

	if(un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
	{
		printf("un_lock failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	return ptr;
}

static int
_db_find_and_lock(DB *db, const char *key, int writelock)
{
	if(!db || !key)
	{
		printf("ERROR!line:%d db :%p, key:%p in function %s\n",
				__LINE__, (void *)db, key, __FUNCTION__);
		exit(-1);
		
	}

	off_t	offset     = 0;
	off_t   nextoffset = 0;

	db->chainoff = (_db_hash(db, key) * PTR_SZ) + db->hashoff;
	db->ptroff   = db->chainoff;

	if(writelock)
	{
		if(write_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
		{
			printf("write_lock failed in function %s()\n",
							__FUNCTION__);
			exit(-1);
		}
		
	}
	else
	{
		if(readw_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
		{
			printf("read_lock failed in function %s\n",
						      __FUNCTION__);

			exit(-1);
		}
	}

	offset = _db_readptr(db, db->ptroff);

	while(offset != 0)
	{
		nextoffset = _db_readidx(db, offset);

		if(strcmp(db->idxbuf, key) == 0)
		{
			break;
		}

		db->ptroff = offset;
		offset = nextoffset;
	}

	return  (offset == 0 ? -1 : 0);
}

static DBHASH
_db_hash(DB *db, const char *key)
{

	if(!db || !key)
	{
		printf("ERROR!line:%d db :%p, key:%p in function %s\n",
				__LINE__, (void*) db, key, __FUNCTION__);
		exit(-1);
	}

	DBHASH	hval = 0;
	char	c    = 0;
	int 	i    = 0;
	
	for(i = 0; (c = *key++) != 0; i++)
	{
		hval += c * i;
	}

	return (hval % db->nhash);
}

static off_t
_db_readptr(DB *db, off_t offset)
{
	if(!db)
	{
		printf("ERROR!line:%d db:%p  in function %s\n",
				__LINE__, (void *)db,  __FUNCTION__);
		exit(-1);
	}

	char	asciiptr[PTR_SZ + 1] = {0,};

	if(lseek(db->idxfd, offset, SEEK_SET) == -1)
	{
		printf("lseek failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	if(read(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
	{
		printf("read failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	asciiptr[PTR_SZ] = 0;

	return (atol(asciiptr));
}

static off_t
_db_readidx(DB *db, off_t offset)
{
	if(!db)
	{
		printf("ERROR!line:%d @db %p in function %s\n",
				__LINE__, (void*) db, __FUNCTION__);
		exit(-1);
	}

	ssize_t		ret = 0;
	char		*ptr1 = NULL;
	char		*ptr2 = NULL;

	char		asciiptr[PTR_SZ + 1]    = {0,};
	char		asciilen[IDXLEN_SZ + 1] = {0,};
	struct iovec	iov[2];

	ret = (offset == 0) ? SEEK_CUR : SEEK_SET;

	if((db->idxoff = lseek(db->idxfd, offset, ret)) == -1)
	{
		printf("lseek failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	iov[0].iov_base = asciiptr;
	iov[0].iov_len  = PTR_SZ;

	iov[1].iov_base = asciilen;
	iov[1].iov_len  = IDXLEN_SZ;

	if((ret = readv(db->idxfd, &iov[0],2)) != PTR_SZ + IDXLEN_SZ)
	{
		if(ret == 0 && offset == 0)
		{
			return -1;
		}

		printf("readv failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	asciiptr[PTR_SZ] = 0;
	db->ptrval = atol(asciiptr);

	asciilen[IDXLEN_SZ] = 0;

	db->idxlen = atoi(asciilen);

	if(db->idxlen < IDXLEN_MIN || db->idxlen > IDXLEN_MAX)
	{
		printf("invalid length in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	if((ret = read(db->idxfd, db->idxbuf, db->idxlen)) != db->idxlen)
	{
		printf("read failed in function %s() line:%d\n",
					__FUNCTION__,__LINE__);
		exit(-1);
	}

	if(db->idxbuf[db->idxlen -1] != NEWLINE)
	{
		printf("missing newline infunction %s\n",__FUNCTION__);
		exit(-1);
	}

	db->idxbuf[db->idxlen - 1] = 0;

	if((ptr1 = strchr(db->idxbuf, SEP)) == NULL)
	{
		printf("strchr failed in function %s()\n",__FUNCTION__);
		printf("missing first separator\n");
		exit(-1);
	}
	*ptr1++ = 0;

	if((ptr2 = strchr(ptr1, SEP)) == NULL)
	{
		printf("strchr failed in function %s()\n",__FUNCTION__);
		printf("missing second separator\n");
		exit(-1);
	}
	*ptr2++ = 0;
	
	if(strchr(ptr2, SEP ) != NULL)
	{
		printf("too many separators line:%d\n",__LINE__);
		exit(-1);
	}

	if((db->datoff = atol(ptr1)) < 0)
	{
		printf("line: %d starting offset < 0\n",__LINE__);
		exit(-1);
	}

	if((db->datlen = atol(ptr2)) < 0)
	{
		printf("invaild length %s()\n",__FUNCTION__);
		exit(-1);
	}

	return db->ptrval;
}

static char* _db_readdat(DB *db)
{
	if(!db)
	{
		printf("ERROR! @db is NULL\n");
		exit(-1);
	}

	if(lseek(db->datfd, db->datoff, SEEK_SET) == -1)
	{
		printf("lseek failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	if(read(db->datfd, db->datbuf, db->datlen) != db->datlen)
	{
		printf("read failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	if(db->datbuf[db->datlen -1] != NEWLINE)
	{
		printf("missing newline in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	db->datbuf[db->datlen -1] = 0;

	return db->datbuf;
}

int db_delete(DBHANDLE h, const char *key)
{
	if(!h || !key)
	{
		printf("ERROR!line:%d h :%p, key:%p in function %s\n",
				__LINE__, (void *)h, key, __FUNCTION__);
		exit(-1);
	}

	DB	*db = h;
	int 	rc  = 0;

	if(_db_find_and_lock(db, key, 1) == 0)
	{
		_db_dodelete(db);
		db->cnt_delok++;
	}
	else
	{
		rc = -1;
		db->cnt_delerr++;
	}

	if(un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
	{
		printf("un_lock failed in function %s()\n",__FUNCTION__);

		exit(-1);
	}

	return rc;
}

static void _db_dodelete(DB * db)
{
	if(!db)
	{
		printf("ERROR! @db is NULL\n");
		exit(-1);
	}
	
	int	i;
	char	*ptr;
	off_t	freeptr, saveptr;
	
	for(ptr = db->datbuf, i = 0; i < db->datlen -1; i++)
	{
		*ptr++ = SPACE;
	}

	*ptr = 0;

	ptr = db->idxbuf;
	while(*ptr)
	{
		*ptr++ = SPACE;
	}

	if(write_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
	{
		printf("write_lock failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	_db_writedat(db, db->datbuf, db->datoff, SEEK_SET);

	freeptr = _db_readptr(db, FREE_OFF);
	
	saveptr = db->ptrval;

	_db_writeidx(db, db->idxbuf, db->idxoff, SEEK_SET, freeptr);

	_db_writeptr(db, FREE_OFF, db->idxoff);

	_db_writeptr(db, db->ptroff, saveptr);

	if(un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
	{
		printf("un_lock failed in function %s()\n",__FUNCTION__);

		exit(-1);
	}

}

static void
_db_writedat(DB *db, const char* data, off_t offset, int whence)
{
	if(!db || !data || offset < 0)
	{
		printf("ERROR!in function %s()\n",__FUNCTION__);
		printf("@db %p\t@data %p\t@offset %zu\n",db, data, offset);
		exit(-1);
	}

	struct iovec	iov[2];
	static char	newline = NEWLINE;
	
	if(whence == SEEK_END)
	{
		if(writew_lock(db->datfd, 0, SEEK_SET, 0) < 0)
		{
			printf("writew_lock failed in function %s\n",
							__FUNCTION__);

			exit(-1);
		}
	}

	if((db->datoff = lseek(db->datfd, offset, whence)) == -1)
	{
		printf("lseek failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	db->datlen = strlen(data) + 1;

	iov[0].iov_base = (char*) data;
	iov[0].iov_len  = db->datlen - 1;

	iov[1].iov_base = &newline;
	iov[1].iov_len  = 1;

	if(writev(db->datfd, &iov[0], 2) != db->datlen)
	{
		if(un_lock(db->datfd, 0, SEEK_SET, 0) < 0)
		{
			printf("un_lock failed in function %s()\n",
							__FUNCTION__);
			exit(-1);
		}
	}
}

static void
_db_writeidx(DB    *db, const char *key, off_t offset,
	    int whence, off_t    ptrval)
{
	if(!db || !key || offset < 0)
	{
		printf("ERROR!in function %s()\n",__FUNCTION__);
		printf("@db %p\t@key %p\t@offset %u\n",
			db, key, (unsigned int)offset);

		exit(-1);
	}

	struct iovec	iov[2];
	char		asciiptrlen[PTR_SZ + IDXLEN_SZ + 1] = {0,};
	ssize_t 	ret = 0;
	int		len  = 0;
	char		*fmt = NULL;
	
	if((db->ptrval = ptrval) < 0 || ptrval > PTR_MAX)
	{
		printf("invalid ptr %p in function %s()\n",
			(void *)ptrval,__FUNCTION__);

		exit(-1);
	}

	if(sizeof(off_t) == sizeof(long long))
	{
		fmt = "%s%c%lld%c%d\n";
	}
	else
	{
		fmt = "%s%c%ld%c%d\n";
	}

	sprintf(db->idxbuf, fmt, key, SEP, db->datoff, SEP, db->datlen);

	if((len = strlen(db->idxbuf)) <  IDXLEN_MIN || len > IDXLEN_MAX)
	{
		printf("invalid length in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	sprintf(asciiptrlen,"%*ld%*d", PTR_SZ,ptrval, IDXLEN_SZ,len);

	if(whence == SEEK_END)
	{
		ret = writew_lock(db->idxfd,
				 ((db->nhash + 1) * PTR_SZ) + 1,
				 SEEK_SET,
				 0);

		if(ret < 0)
		{
			printf("writew_lock failed in function %s()\n",
							__FUNCTION__);
			exit(-1);
		}
	}

	if((db->idxoff = lseek(db->idxfd, offset, whence)) == -1)
	{
		printf("lseek failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	iov[0].iov_base = asciiptrlen;
	iov[0].iov_len  = PTR_SZ + IDXLEN_SZ;

	iov[1].iov_base = db->idxbuf;
	iov[1].iov_len  = len;

	if(writev(db->idxfd, &iov[0],2) != PTR_SZ + IDXLEN_SZ + len)
	{
		printf("writev failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	if(whence == SEEK_END)
	{
		ret = un_lock(db->idxfd,
			      ((db->nhash + 1) * PTR_SZ) + 1,
			      SEEK_SET,
			      0);

		if(ret < 0)
		{
			printf("un_lock failed in function %s()\n",
							__FUNCTION__);
			exit(-1);
		}
	}
}

static void _db_writeptr(DB *db, off_t offset, off_t ptrval)
{
	if(!db || offset < 0 || !ptrval)
	{
		printf("ERROR!in function %s()\n",__FUNCTION__);
		printf("@db %p\t@offset %u\t ptrval %p\n",
			db, (unsigned int)offset,(void *)ptrval);

		exit(-1);
	}

	char asciiptr[PTR_SZ + 1] = {0,};
	
	if(ptrval < 0 || ptrval > PTR_MAX)
	{
		printf("invalid ptr %p in function %s()\n",(void *)ptrval,__FUNCTION__);
		exit(-1);
	} 

	sprintf(asciiptr,"%*ld",PTR_SZ, ptrval);

	if(lseek(db->idxfd, offset, SEEK_SET) == -1)
	{
		printf("lseek faild in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	if(write(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
	{
		printf("write failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}
	
}

int db_store(DBHANDLE h,const char *key, const char *data, int flag)
{
	if(!h || !key || !data)
	{
		printf("ERROR!in function %s()\n",__FUNCTION__);
		printf("@h %p\t@key %p\t data %p\n", h, key, data);

		exit(-1);
	}

	DB	*db = h;

	int      rc     = 0;
	int      keylen = 0;
	int      datlen = 0;

	off_t    ptrval = 0;
	
	if(flag != DB_INSERT  && 
	   flag != DB_REPLACE &&
	   flag != DB_STORE)
	{
		errno = EINVAL;
		return -1;
	}

	keylen = strlen(key);
	datlen = strlen(data) + 1;

	if(datlen < DATLEN_MIN || datlen > DATLEN_MAX )
	{
		printf("invalid data length in function %s\n",
						__FUNCTION__);
		exit(-1);
	}

	if(_db_find_and_lock(db, key, 1) < 0)
	{
		if(flag == DB_REPLACE)
		{
			rc = -1;
			db->cnt_storerr++;
			errno = ENOENT;

			goto doreturn;
		}

		ptrval = _db_readptr(db, db->chainoff);
		
		if(_db_findfree(db, keylen, datlen) < 0)
		{
			_db_writedat(db, data, 0, SEEK_END);
			_db_writeidx(db, key,  0, SEEK_END, ptrval);
			_db_writeptr(db, db->chainoff, db->idxoff);
			db->cnt_stor1++;
		}
		else
		{
			_db_writedat(db, data, db->datoff, SEEK_SET);
			_db_writeidx(db, key,  db->idxoff, SEEK_SET, ptrval);
			_db_writeptr(db, db->chainoff, db->idxoff);
			db->cnt_stor2++;
			
		}
	}
	else
	{
		if(flag == DB_INSERT)
		{
			rc = 1;
			db->cnt_storerr++;
			goto doreturn;
		}

		if(datlen != db->datlen)
		{
			_db_dodelete(db);
			ptrval = _db_readptr(db, db->chainoff);

			_db_writedat(db, data, 0, SEEK_END);
			_db_writeidx(db,  key, 0, SEEK_END, ptrval);
			_db_writeptr(db, db->chainoff, db->idxoff);

			db->cnt_stor3++;
		}
		else
		{
			_db_writedat(db, data, db->datoff, SEEK_SET);

			db->cnt_stor4++;
		}
	}

	rc = 0;

doreturn:
	if(un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
	{
		printf("un_lock failed in functin %s()\n",__FUNCTION__);
		exit(-1);
	}

	return rc;
}

static int
_db_findfree(DB *db, int keylen, int datlen)
{
	if(!db || keylen < 0 || datlen < 0)
	{
		printf("ERROR!in function %s()\n",__FUNCTION__);
		printf("@db %p\t@keylen %u\t datalen %u\n",db, keylen, datlen);

		exit(-1);
	}

	int   rc 	 = 0;
	off_t offset     = 0;
	off_t nextoffset = 0;
	off_t saveoffset = 0;

	if(writew_lock(db->idxfd, FREE_OFF, SEEK_SET,1) < 0)
	{
		printf("writew_lock failed in function %s()\n",__FUNCTION__);

		exit(-1);
	}

	saveoffset = FREE_OFF;
	offset     = _db_readptr(db, saveoffset);

	while(offset != 0)
	{
		nextoffset = _db_readidx(db, offset);

		if(strlen(db->idxbuf) == keylen && db->datlen == datlen)
		{
			break;
		}

		saveoffset = offset;
		offset = nextoffset;
	}

	if(offset == 0)
	{
		return -1;
	}
	else
	{
		_db_writeptr(db, saveoffset, db->ptrval);
		rc = 0;
	}

	if(un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
	{
		printf("un_lock failed in function %s()",__FUNCTION__);
		exit(-1);
	}

	return rc;
}

void db_rewind(DBHANDLE h)
{
	if(!h)
	{
		printf("%s failed DBHANDLE @h is NULL\n",__FUNCTION__);
		exit(-1);
	}

	DB	*db    = h;
	off_t	offset = 0;
	
	offset = (db->nhash + 1) * PTR_SZ;

	if((db->idxoff = lseek(db->idxfd, offset + 1, SEEK_SET)) < 0)
	{
		printf("lseek failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

}

char* 
db_nextrec(DBHANDLE h, char *key)
{
	if(!h || !key)
	{
		printf("%s failed\n",__FUNCTION__);
		printf("@h %p\t @key %p\n",h, key);
		exit(-1);
	}

	DB	*db  = h;
	char	c    = 0;
	char	*ptr = NULL;

	if(read_lock(db->idxfd, FREE_OFF, SEEK_SET,1) < 0)
	{
		printf("read_lock failed in function %s()\n",__FUNCTION__);
		exit(-1);
	}

	do
	{
		if(_db_readidx(db, 0) < 0)
		{
			ptr = NULL;
			goto doreturn;
		}

		ptr = db->idxbuf;

		while((c = *ptr++) != 0 && c == SPACE)
		{
		}
	}while(c == 0);

	if(key != NULL)
	{
		strcpy(key, db->idxbuf);
	}

	ptr = _db_readdat(db);

	db->cnt_nextrec++;

doreturn:
	if(un_lock(db->idxfd, FREE_OFF, SEEK_SET ,1) < 0)
	{
		printf("un_lock failed in function %s\n",__FUNCTION__);
		exit(-1);
	}

	return ptr;
}
