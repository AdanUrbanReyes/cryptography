#include <stdio.h>
#include <string.h>
#include "unidimensionalMatrix.h"
#include "algorithms.h"
#include "hillCipher.h"
#define LENGHTALPHABET 26
int main(int ari,char **arc){
	int option;
	unsigned int sok;//sizeof key
	int *key=NULL;
	char *pathInFile=(char *)malloc(sizeof(char)*400);
	char *pathOutFile=(char *)malloc(sizeof(char)*400);
	do{
		printf("\t\t\tingrese una opcion\n\t1. calcular determinante de una matriz\n\t2. determinar si una matriz tiene inverza\n\t3. calcular la inverza de una matriz\n\t4. encriptar usando hill cipher\n\t5. desencriptar usando hill cipher\n\t-1. para saliri\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				printf("ingrese el tamano de la matriz: ");
				scanf("%u",&sok);
				key=getMemoryForIntegerUnidimensionalMatrix(sok,sok);
				key=fillBySTDINIntegerUnidimensionalMatrix(key,sok,sok);
				printf("matriz ingresada:\n");
				printIntegerUnidimensionalMatrix(key,sok,sok);
				printf("determinante de la matriz=%d\n",determinantIntegerUnidimensionalMatrix(key,sok,sok));
			break;
			case 2:
				printf("ingrese el tamano de la matriz: ");
				scanf("%u",&sok);
				key=getMemoryForIntegerUnidimensionalMatrix(sok,sok);
				key=fillBySTDINIntegerUnidimensionalMatrix(key,sok,sok);
				printf("matriz ingresada:\n");
				printIntegerUnidimensionalMatrix(key,sok,sok);
				if(hasInverseIntegerUnidimensionalMatrix(key,sok,sok,LENGHTALPHABET)==1){
					printf("SI tiene inversa\n");
				}else{
					printf("NO tiene inversa\n");
				}
			break;
			case 3:
				printf("ingrese el tamano de la matriz: ");
				scanf("%u",&sok);
				key=getMemoryForIntegerUnidimensionalMatrix(sok,sok);
				key=fillBySTDINIntegerUnidimensionalMatrix(key,sok,sok);
				printf("matriz ingresada:\n");
				printIntegerUnidimensionalMatrix(key,sok,sok);
				printf("matriz inversa:\n");
				printIntegerUnidimensionalMatrix(inverseIntegerUnidimensionalMatrix(key,sok,sok,LENGHTALPHABET),sok,sok);
			break;
			case 4:
				printf("ingrese el tamano de la matriz llave: ");
				scanf("%u",&sok);
				key=getMemoryForIntegerUnidimensionalMatrix(sok,sok);
				key=fillBySTDINIntegerUnidimensionalMatrix(key,sok,sok);
				printf("ingrese el path del archivo a cifrar (no mas de 400 caracteres): ");
				scanf("%s",pathInFile);
				printf("ingrese el path del archivo de salida (no mas de 400 caracteres): ");
				scanf("%s",pathOutFile);
				encryptFileWithHillCipher(pathInFile,key,sok,sok,pathOutFile);
				printf("se a cifrado (solo caracteres alphabeticos) el contenido del archivo %s con la matriz llave ingresada:\n",pathInFile);
				printIntegerUnidimensionalMatrix(key,sok,sok);
				printf("y se a guardado el texto cifrado en %s\n",pathOutFile);
			break;
			case 5:
				printf("ingrese el tamano de la matriz llave: ");
				scanf("%u",&sok);
				key=getMemoryForIntegerUnidimensionalMatrix(sok,sok);
				key=fillBySTDINIntegerUnidimensionalMatrix(key,sok,sok);
				printf("ingrese el path del archivo a cifrar (no mas de 400 caracteres): ");
				scanf("%s",pathInFile);
				printf("ingrese el path del archivo de salida (no mas de 400 caracteres): ");
				scanf("%s",pathOutFile);
				descryptFileWithHillCipher(pathInFile,key,sok,sok,pathOutFile);
				printf("se a descifrado (solo caracteres alphabeticos) el contenido del archivo %s con la matriz llave ingresada:\n",pathInFile);
				printIntegerUnidimensionalMatrix(key,sok,sok);
				printf("y se a guardado el texto descifrado en %s\n",pathOutFile);
			break;
			case -1: 
				printf("hasta pronto :D\n");
			break;
			default: printf("opcion no valida :( \n");
		}
	}while(option!=-1);
	return 0;
}
