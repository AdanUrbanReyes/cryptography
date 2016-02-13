#include <stdio.h>
#include <mysql/mysql.h>
#ifndef __MYSQL_H__
#define __MYSQL_H__
#define LENGHTQUERY 400//size of query on charactares
MYSQL *connection;//connection
MYSQL_RES *response;//here storage the response of a query on mysql
MYSQL_ROW tupla;//here storage the tuplas getting with response
char query[LENGHTQUERY];//query
short startConnection(char *,char *,char *);
short selectDatabase(char *);
short executeQuery(char *);
#endif
