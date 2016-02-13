#include <stdio.h>
#include "algoriths.h"
int main(int ari,char **arc){
	//./a.out -d "N SARB QG ZMMA  L XMR LY" "FIND" example for descrypt the message NSARB QG... with key FIND
	//./a.out -e "MAKE IT HAPPEN" "MATH" example for encrypt the message MAKE IT ... with key MATH
	if(ari<4){
		printf("error ejecute como %s -d|-e \"texto a encriptar|desencriptar usando vigenere\" \"llave\"",arc[0]);
		return 0;
	}
	char *ivs=NULL;//is vigenere string
	printf("texto: |%s|\n",arc[2]);
	printf("llave: |%s|\n",arc[3]);
	ivs=isVigenereString(arc[2]);
	if(ivs!=NULL){
		printf("el texto contiene caracter(es) que no se usan en vigenere (%c) remueva este caracter y vuelva a intentarlo\n",*ivs);
		return 0;
	}
	ivs=isVigenereString(arc[3]);
	if(ivs!=NULL){
		printf("la llave contiene caracter (es) que no se usan en vigenere (%c) remueva ese caracter y vuelva a intentarlo\n",*ivs);
		return 0;
	}
/*	
	if(!memcmp(arc[1],"-e",sizeof(char)*2)){
		printf("encriptacion vigenere: |%s|\n",encryptWithVigenere(arc[2],arc[3]));
	}else{
		if(!memcmp(arc[1],"-d",sizeof(char)*2)){
			printf("desencriptacion vigenere: |%s|\n",descryptWithVigenere(arc[2],arc[3]));
		}else{
			printf("la opcion %s no es reconicida solo -d para desencriptar y -e para encriptar\n",arc[1]);
		}
	}
*/
	return 0;
}
