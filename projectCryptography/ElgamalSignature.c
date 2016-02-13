#include "ElgamalSignature.h"
short createTableElgamalSignature(){
	sprintf(query,"create table if not exists ElgamalSignature(idUser char(%u) not null,primeNumber int unsigned not null,generator int unsigned not null,privateKey int unsigned not null,ya int unsigned not null,beta int unsigned not null,MD5 char(%u) not null,hash int unsigned not null,primary key(MD5),foreign key(idUser) references User(id) on delete cascade on update cascade);",LENGHTID,MD5_LEN);
	return executeQuery(query);
}
short insertElgamalSignature(ElgamalSignature elgamalSignature){
	sprintf(query,"insert into ElgamalSignature value(\'%s\',%u,%u,%u,%u,%u,\'%s\',%u);",elgamalSignature.idUser,elgamalSignature.publicKey.primeNumber,elgamalSignature.publicKey.generator,elgamalSignature.privateKey,elgamalSignature.publicKey.ya,elgamalSignature.beta,elgamalSignature.MD5,elgamalSignature.hash);
	return executeQuery(query);
}
ElgamalSignature getElgamalSignature(char *MD5){
	sprintf(query,"select * from ElgamalSignature where MD5=\'%s\';",MD5);
	ElgamalSignature elgamalSignature;
	bzero(&elgamalSignature,sizeof(ElgamalSignature));
	if(executeQuery(query)==-1){
		return elgamalSignature;
	}
	/*response=mysql_store_result(connection);
	if(response){
		printf("\t\t\t\tnumberFields = %u\n",mysql_num_fields(response));
				  printf("\t\t\t\tfilecount = %u\n",mysql_field_count(connection));
	}
	*/
	response=mysql_use_result(connection);
	while ((tupla = mysql_fetch_row(response)) != NULL){
		sscanf(tupla[0],"%s",elgamalSignature.idUser);
		sscanf(tupla[1],"%u",&elgamalSignature.publicKey.primeNumber);
		sscanf(tupla[2],"%u",&elgamalSignature.publicKey.generator);
		sscanf(tupla[3],"%u",&elgamalSignature.privateKey);
		sscanf(tupla[4],"%u",&elgamalSignature.publicKey.ya);
		sscanf(tupla[4],"%u",&elgamalSignature.beta);
		sscanf(tupla[6],"%s",elgamalSignature.MD5);
		sscanf(tupla[7],"%u",&elgamalSignature.hash);
	}
	return elgamalSignature;
}
