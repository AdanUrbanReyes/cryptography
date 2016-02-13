#include <stdio.h>
#include <string.h>
#include "mysql.h"
#ifndef __USER_H__
#define __USER_H__
#define LENGHTID 10
#define LENGHTNAME 30
typedef struct User{
	char id[LENGHTID+1];//plus one for character end of line
	char name[LENGHTNAME+1];//plus one for character end of line
}User;
short createTableUser();
short insertUser(User );
User getUser(char *);
#endif
