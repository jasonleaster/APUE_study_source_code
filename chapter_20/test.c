#include "apue_db.h"
#include <stdio.h>
#include <fcntl.h>

#define STRING_SZ 100
#define DATA_SET  3

int main()
{

	char str_key[DATA_SET][STRING_SZ] = {
					      {"Alpha"},
					      {"Belta"},
					      {"Gama"}
					     };

	char str_dat[DATA_SET][STRING_SZ] = {
					      {"data1"},
					      {"data2"},
				     	      {"data3"}
				    	    };

	DBHANDLE handler = db_open("./database",
				   O_CREAT | O_TRUNC | O_RDWR,
				   FILE_MODE);


	if(db_store(handler,str_key[0],str_dat[0],DB_INSERT) != 0)
	{
		printf("Error! db_store failed in function %s\n",
			                            __FUNCTION__);

		printf("Trying to store key:%s\t data:%s\n",
				      str_key[0],str_dat[0]);

		goto failed;
	}

	if(db_store(handler,str_key[1],str_dat[1],DB_INSERT) != 0)
	{
		printf("Error! db_store failed in function %s\n",
			                            __FUNCTION__);

		printf("Trying to store key:%s\t data:%s\n",
				      str_key[1],str_dat[1]);

		goto failed;
	}

	if(db_store(handler,str_key[2],str_dat[2],DB_INSERT) != 0)
	{
		printf("Error! db_store failed in function %s\n",
			                            __FUNCTION__);

		printf("Trying to store key:%s\t data:%s\n",
				      str_key[2],str_dat[2]);

		goto failed;
	}

failed:
	db_close(handler);

	return 0;
}
