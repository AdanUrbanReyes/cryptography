#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include "counterMode.h"
#include "signatureGAMAL.h"
#include "User.h"
#include "FileCipherWithDES.h"
#include "ElgamalSignature.h"
extern User user;
void managementKeys(){
	system("clear");
	List list=getUserPublicKey();
	UserPublicKey userPublicKey;
	printf("|%30s|%12s|%12s|%12s|\n","nombre de usuario","numero primo","generador","YA");
	while(list.head!=NULL){
		userPublicKey=*((UserPublicKey *)list.head->data);
		printf("|%30s|%12u|%12u|%12u|\n",userPublicKey.nameUser,userPublicKey.publicKey.primeNumber,userPublicKey.publicKey.generator,userPublicKey.publicKey.ya);
		list.head=list.head->next;
	}
	getchar();
}
void addSignature(){
	system("clear");
	ElgamalSignature elgamalSignature;
	char pathInFile[PATH_LEN];
	printf("Porfavor ingrese el path del archivo a firmar: ");
	scanf("%s",pathInFile);
	getchar();
	elgamalSignature=signatureGAMAL(pathInFile);
	//falta un if
		//printf("Error al firmar el archivo %s porfavor vuelva a intentarlo\n",pathInFile);
//		return ;
//	}
	printf("Archivo %s firmado correctamente\nLlave publica generada:\nnumero primo: %u\ngenerador: %u\nYA: %u\n",pathInFile,elgamalSignature.publicKey.primeNumber,elgamalSignature.publicKey.generator,elgamalSignature.publicKey.ya);
	getchar();
}
void encryptDocument(){
	system("clear");
	char pathInFile[PATH_LEN],pathOutFile[PATH_LEN];
	printf("Porfavor ingrese el path del archivo a cifrar: ");
	scanf("%s",pathInFile);
	getchar();
	printf("Porfavor ingrese el path del archivo que desea como salida: ");
	scanf("%s",pathOutFile);
	getchar();
	if(cipher(pathInFile,pathOutFile)<0){
		printf("Error al cifrar el archivo %s porfavor vuelva a intentarlo\n",pathInFile);
		getchar();
		return ;
	}
	printf("Archivo %s cifrado correctamente y salvado como %s\n",pathInFile,pathOutFile);
	getchar();
}
void addSignatureAndCipherDocument(){
	system("clear");
	char pathInFile[PATH_LEN],pathOutFile[PATH_LEN];
	printf("Porfavor ingrese el path del archivo a firmar y cifrar: ");
	scanf("%s",pathInFile);
	getchar();
	printf("Porfavor ingrese el path del archivo que desea como salida: ");
	scanf("%s",pathOutFile);
	getchar();
	ElgamalSignature elgamalSignature=signatureGAMAL(pathInFile);
	//falta un if si falla lo de arriva!!!
//	if(signatureGAMAL(pathInFile)<0){
//		printf("Error al firmar el archivo %s porfavor vuelva a intentarlo\n",pathInFile);
//		return ;
//	}
	printf("Archivo %s firmado correctamente\nLlave publica generada:\nnumero primo: %u\ngenerador: %u\nYA: %u\n",pathInFile,elgamalSignature.publicKey.primeNumber,elgamalSignature.publicKey.generator,elgamalSignature.publicKey.ya);
	if(cipher(pathInFile,pathOutFile)<0){
		printf("Error al cifrar el archivo %s porfavor vuelva a intentarlo (solo la opcion de cifrar ya que si fue firmado)\n",pathInFile);
		getchar();
		return ;
	}
	printf("Archivo %s firmado y cifrado correctamente y salvado como %s\n",pathInFile,pathOutFile);
	getchar();
}
void verifySignarute(){
	system("clear");
	char pathFile[PATH_LEN];
	printf("Porfavor ingrese el path del archivo a verificar firmar: ");
	scanf("%s",pathFile);
	getchar();
	if(verifySignatureGAMAL(pathFile)>=0){
		printf("Error el archivo %s no corresponde con los datos de la persona que lo firmo\n",pathFile);
		getchar();
		return ;
	}
	printf("La firma del archivo %s corresponde con los datos de la persona que lo firmo\n",pathFile);
	getchar();
}
void decryptDocument(){
	system("clear");
	char pathInFile[PATH_LEN],pathOutFile[PATH_LEN];
	printf("Porfavor ingrese el path del archivo a desifrar: ");
	scanf("%s",pathInFile);
	getchar();
	printf("Porfavor ingrese el path del archivo que desea como salida: ");
	scanf("%s",pathOutFile);
	getchar();
	if(descipher(pathInFile,pathOutFile)<0){
		printf("Error al decifrar el archivo %s al paracer no fue cifrado con este sistema\n",pathInFile);
		getchar();
		return ;
	}
	printf("Archivo %s decifrado correctamente\n",pathInFile);
	/*if(wasSignature()==0){
		printf("El archivo %s fue firmado se procede a verficar la firma\n",pathInFile);
		if(verifySignatureGAMAL(pathOutFile)==0){
			printf("Error la firma del archivo no corresponde con los datos de la persona que lo firmo\n");
			return ;
		}
		printf("La firma corresponde con los datos de la persona que lo firmo\n");
	}*/
	getchar();
}
void menu2(){
	short option;
	system("clear");
	printf("\t\t\tBienbenido %s te estabamos esperando :D\n",user.name);
	sleep(1);
	do{
		system("clear");
		printf("Elije una opcion\n\t1 Administracion de llaves\n\t2 Agregar firma a un documento\n\t3 Cifrar documento\n\t4 Agregar firma a un documento y cifrarlo\n\t5 Descifrar un documento\n\t6 Verificar firma\n\t-1 Salir\n");
		scanf("%hd",&option);
		getchar();
		switch(option){
			case 1: managementKeys(); break;
			case 2: addSignature(); break;
			case 3: encryptDocument(); break;
			case 4: addSignatureAndCipherDocument(); break;
			case 5: decryptDocument(); break;
			case 6: verifySignarute(); break;
			case -1: printf("\t\tvuelve pronto %s\n",user.name); break;
			default: printf("%hd Esta no es una opcion\n",option);
		}
	}while(option!=-1);
}
void registerUser(){
	system("clear");
	printf("\t\tIngresa los siguientes datos\n");
	printf("Nombre (30 caracteres maximo): ");
	fgets(&(user.name[0]),LENGHTNAME,stdin);
	printf("Boleta: (10 caracteres maximo): ");
	scanf("%s",&(user.id[0]));
	getchar();
	user.name[strlen(user.name)-1]='\0';//remove jump of line (\n)
	if(insertUser(user)==-1){
		fprintf(stderr,"Error no se pudo registrar el usuario %s con id %s\n%s\n",user.name,user.id,mysql_error(connection));
		return;
	}
	printf("\n\t\t\tFelicidades as sido registrado exitosamente %s con boleta %s\n\n",user.name,user.id);
	getchar();
}
void login(){
	system("clear");
	char id[LENGHTID+1];//plus one by character end of line
	printf("ingrese su id (10 caracteres maximo): ");
	scanf("%s",id);
	getchar();
	user=getUser(id);
	if(!strcmp(user.name,"000000000000000000000000000000")){//the query failure: CORREGIR ESTO!!!
		printf("error usuario con id %s no encontrado\n",id);
		getchar();
		return ;
	}
	menu2();
}
short createDatabase(){
	if(startConnection("localhost","root","ayani13711?")==-1){
		fprintf(stderr, "Error al conectar con mysql\n%s\n", mysql_error(connection));
		return -1;
	}
	strcpy(query,"create schema if not exists secureDocuments1;");	
	if(executeQuery(query)==-1){
		fprintf(stderr, "Error al crear el esquema secureDocuments1\n%s\n", mysql_error(connection));
		return -2;
	}
	selectDatabase("secureDocuments1");//is imposible that failed becuase pass anterior if
	if(createTableUser()==-1){
		fprintf(stderr, "Error al crear la tabla User \n%s\n", mysql_error(connection));
		return -3;
	}
	if(createTableFileCipherWithDES()==-1){
		fprintf(stderr, "Error al crear la tabla FileCipherWithDES\n%s\n", mysql_error(connection));
		return -4;
	}
	if(createTableElgamalSignature()==-1){
		fprintf(stderr, "Error al crear la tabla ElgamalSignature\n%s\n", mysql_error(connection));
		return -5;
	}
	return 0;
}
int main(int ari,char **arc){
	loadTables("tables.dat");
	if(createDatabase()<0){
		printf("Lamentamos las fallas con la base de datos solucionaremos esto lo mas pronto posible\n");
		return -1;
	}
	setNumberLinesOfFileWithPrimeNumbersAndGenerators(getNumberLinesFile(PATHFILEWITHPRIMESANDGENERATORS));
	setSeed(time(NULL));
	short option;
	do{
		system("clear");
		printf("Elije una opcion\n\t1 Registrar\n\t2 Ingresar\n\t-1 Salir\n");
		scanf("%hd",&option);
		getchar();
		switch(option){
			case 1: registerUser(); break;
			case 2: login(); break;
			case -1: printf("\n\t\tHasta luego, gracias por usar el sistema\n"); break;
			default: printf("%hd Esta no es una opcion\n",option);
		}
	}while(option!=-1);
	return 0;
}
