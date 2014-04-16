/************************************************************
just a implementation of getpwname function
*************************************************************/
#include "pwd.h"
#include "stdef.h"
#include "string.h"

struct passwd*
getpwname(const char*name)
{
	struct passwd* ptr = NULL;
	setpwent();
	
	while((ptr = getpwent()) != NULL)
	{
		if((strcmp(name,ptr->pw_name)) == 0)
		{
			break;
		}

		endpwent();
	}
	
	return ptr;
}
