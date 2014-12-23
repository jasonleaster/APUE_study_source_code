#ifndef _APUE_DB_H
#define _APUE_DB_H

	typedef void* DBHANDLE;
	
	DBHANDLE db_open(const char*, int , ...);
	void     db_close(DBHANDLE);
	char    *db_fetch(DBHANDLE, const char*);
	int      db_store(DBHANDLE, const char*, const char*, int);
	int      db_delete(DBHANDLE h, const char *key);
	void     db_rewind(DBHANDLE);
	char     *db_nextrec(DBHANDLE, char*);
	
	/*
	**  Flags for db_store()
	*/


	#define DB_INSERT  (1)
	#define DB_REPLACE (2)
	#define DB_STORE   (3)
	
	/*
	** Implementation limits.
	*/

	#define IDXLEN_MIN (6)
	#define IDXLEN_MAX (1024)
	#define DATLEN_MIN (2)
	#define DATLEN_MAX (1024)


#endif
