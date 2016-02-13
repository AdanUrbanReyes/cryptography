#include <stdio.h>
#include "shiftCipher.h"
void printErrorExecute(char *nameExecute){
		printf("\t\t\tERROR!\n\t\t\tposibles formas de correr este programa\n");
		printf("\t1. si quiere encriptar un texto que esta dentro de un archivo ejecute como: %s -e pathAbsolutoArchivo llave nombreArchivoSalida\n",nameExecute);
		printf("\t2. si quiere desencriptar un texto que esta dentro de un archivo ejecute como: %s -d pathAbsolutoArchivo llave nombreArchivoSalida\n",nameExecute);
		printf("\t3. si quiere \"hackear\" usando fuerza bruta ejecute como %s -h pathAbsolutoArchivo nombreArchivoSalida\n",nameExecute);
}
int main(int ari,char **arc){//./a.out -e/-d nameFileIn key nameFileOut
	if(ari<4){
		printErrorExecute(arc[0]);
		return -1;
	}
	if(!memcmp(arc[1],"-e",2)){//then will encrypt
		if(encryptFileWithShiftCipher(arc[2],atoi(arc[3]),arc[4])<0){
			printf("error al encriptar el archivo %s y tratar de guardarlo en %s\nintentelo de nuevo\n",arc[2],arc[4]);
		}else{
			printf("archivo %s encriptado y guardado en %s\n",arc[2],arc[4]);
		}	
	}else{
		if(!memcmp(arc[1],"-d",2)){//then will descrypt
			if(decryptFileWithShiftCipher(arc[2],atoi(arc[3]),arc[4])<0){
				printf("error al desencriptar el archivo %s y tratar de guardarlo en %s\nintentelo de nuevo\n",arc[2],arc[4]);
			}else{
				printf("archivo %s desencriptado y guardado en %s\n",arc[2],arc[4]);
			}		
		}else{
			if(!memcmp(arc[1],"-h",2)){
				if(hackByBruteForce(arc[2],arc[3])<0){
					printf("error al \"hackear\" el archivo %s y tratar de guardarlo en %s\nintentelo de nuevo\n",arc[2],arc[3]);
				}else{
					printf("archivo %s \"hackeado\" y guardado en %s\n",arc[2],arc[3]);
				}		
			}else{
				printErrorExecute(arc[0]);
			}
		}
	}
	return 0;
}
