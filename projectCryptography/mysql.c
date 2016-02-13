#include "mysql.h"
short startConnection(char *server,char *user,char *password){
	connection=mysql_init(NULL);
	return (mysql_real_connect(connection,server,user,password,NULL,0,NULL,0)==0) ? -1 : 0;
}
short selectDatabase(char *nameDatabase){
	sprintf(query,"use %s;",nameDatabase);
	return (mysql_query(connection,query)!=0) ? -1 : 0;
}
short executeQuery(char *query){
	return (mysql_query(connection,query)!=0) ? -1 : 0;
}
