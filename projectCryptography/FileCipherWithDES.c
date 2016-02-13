#include "FileCipherWithDES.h"
short createTableFileCipherWithDES(){
	sprintf(query,"create table if not exists FileCipherWithDES(idUser char(%u) not null,MD5 char(%u) not null,initialVector bigint unsigned not null,llave bigint unsigned not null,primary key(MD5), foreign key(idUser) references User(id) on delete cascade on update cascade);",LENGHTID,MD5_LEN);
	return executeQuery(query);
}
short insertFileCipherWithDES(FileCipherWithDES fileCipherWithDES){
	sprintf(query,"insert into FileCipherWithDES value(\'%s\',\'%s\',%" PRIu64 ",%"PRIu64 ");",fileCipherWithDES.idUser,fileCipherWithDES.MD5,fileCipherWithDES.initialVector,fileCipherWithDES.key);
	return executeQuery(query);
}
FileCipherWithDES getFileCipherWithDES(char *MD5){
	sprintf(query,"select * from FileCipherWithDES where MD5=\'%s\';",MD5);
	FileCipherWithDES fileCipherWithDES;
	bzero(&fileCipherWithDES,sizeof(FileCipherWithDES));
	if(executeQuery(query)==-1){
		return fileCipherWithDES;
	}
	response=mysql_use_result(connection);
	while ((tupla = mysql_fetch_row(response)) != NULL){
		sscanf(tupla[0],"%s",fileCipherWithDES.idUser);
		sscanf(tupla[1],"%s",fileCipherWithDES.MD5);
		sscanf(tupla[2],"%" PRIu64 ,&fileCipherWithDES.initialVector);
		sscanf(tupla[3],"%" PRIu64 ,&fileCipherWithDES.key);
	}
	return fileCipherWithDES;
}
