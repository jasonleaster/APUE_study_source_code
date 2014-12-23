#include "apue_db.h"
#include <stdio.h>
#include <fcntl.h>

int
main(void)
{
	DBHANDLE	db;

	if ((db = db_open("db4", O_RDWR | O_CREAT | O_TRUNC,
	  FILE_MODE)) == NULL)
		printf("db_open error");

	if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
		printf("db_store error for alpha");
	if (db_store(db, "beta", "Data for beta", DB_INSERT) != 0)
		printf("db_store error for beta");
	if (db_store(db, "gamma", "record3", DB_INSERT) != 0)
		printf("db_store error for gamma");

	db_close(db);
	exit(0);
}
