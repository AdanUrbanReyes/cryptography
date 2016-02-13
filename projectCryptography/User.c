#include "User.h"
short createTableUser(){
	sprintf(query,"create table if not exists User(id char(%u) not null,name char(%u) not null, primary key(id));",LENGHTID,LENGHTNAME);
	return executeQuery(query);
}
short insertUser(User user){
	
	sprintf(query,"insert into User value(\'%s\',\'%s\');",user.id,user.name);
	return executeQuery(query);
}
User getUser(char *id){//id of user
	sprintf(query,"select * from User where id=\'%s\';",id);
	User user;
	bzero(&user,sizeof(User));
	if(executeQuery(query)==-1){
		return user;
	}
	/*response=mysql_store_result(connection);
	if(response){
		printf("\t\t\t\tnumberFields = %u\n",mysql_num_fields(response));
				  printf("\t\t\t\tfilecount = %u\n",mysql_field_count(connection));
	}
	*/
	response=mysql_use_result(connection);
	while ((tupla = mysql_fetch_row(response)) != NULL){
		sscanf(tupla[0],"%s",user.id);
		sscanf(tupla[1],"%[A-Za-z ]",user.name);
	}
	return user;
}
