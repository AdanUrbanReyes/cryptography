#include <stdio.h>
#include <string.h>

#include "advantaceEncryptionStandard.h"
void inversePolynomial(char **arc){
	unsigned int polynomial=0,irreduciblePolynomial=0;
	if(!memcmp(arc[2],"-h",2*sizeof(char))){//enter polinomials on format hexadecimal
		sscanf(arc[3],"%x",&polynomial);	
		sscanf(arc[4],"%x",&irreduciblePolynomial);	
	}else{
		if(!memcmp(arc[2],"-d",2*sizeof(char))){
			sscanf(arc[3],"%u",&polynomial);	
			sscanf(arc[4],"%u",&irreduciblePolynomial);	
		}else{
			if(!memcmp(arc[2],"-s",2*sizeof(char))){
				polynomial=convertPolynomialS(arc[3]);
				irreduciblePolynomial=convertPolynomialS(arc[4]);
			}else{
				printf("\tERROR %s no es una opcion valida para este tipo de ejecucion (calcular el inverso de un polinomio), solo se cuenta con las siguientes opciones:\n",arc[2]);
				printf("-h \"polinomio en formato hexadecimal\" \"polinomio irreducible en formato hexadecimal\"\n");
				printf("-d \"polinomio en formato decimal\" \"polinomio irreducible en formato decimal\"\n");
				printf("-s \"polinomio en formato string\" \"polinomio irreducible en formato string\"\n");
				printf("Nota: para el formato string ingresar las potencias con el simbolo \"^\" y si es una potencia 0 poner un uno ejemplo x^5+x^4+x^2+x^1+1\n");
				return;
			}
		}
	}
	printf("el inverso de %x en %x es = %x\n",polynomial,irreduciblePolynomial,extendedEuclides(polynomial,irreduciblePolynomial));
}
void convertPolynomialToString(char **arc){
	unsigned int polynomial=0;
	if(!memcmp(arc[2],"-h",2*sizeof(char))){//enter polinomials on format hexadecimal
		sscanf(arc[3],"%x",&polynomial);	
		printf("el polynomio %x = %s\n",polynomial,convertPolynomialUI(polynomial,'x'));
	}else{
		if(!memcmp(arc[2],"-d",2*sizeof(char))){
			sscanf(arc[3],"%u",&polynomial);	
			printf("el polynomio %d = %s\n",polynomial,convertPolynomialUI(polynomial,'x'));
		}else{
			printf("\tERROR %s no es una opcion valida para este tipo de ejecucion (convertir polynomio a formato string), solo se cuenta con las siguientes opciones:\n",arc[2]);
			printf("-h \"polinomio en formato hexadecimal\"\n");
			printf("-d \"polinomio en formato decimal\"\n");
			return;
		}
	}
}
void inversesField(char **arc){
	unsigned char n=atoi(arc[2]);
	char *pathFile=arc[5];
	unsigned int irreduciblePolynomial=0;
	if(!memcmp(arc[3],"-h",2*sizeof(char))){//enter polinomials on format hexadecimal
		sscanf(arc[4],"%x",&irreduciblePolynomial);	
	}else{
		if(!memcmp(arc[3],"-d",2*sizeof(char))){
			sscanf(arc[4],"%u",&irreduciblePolynomial);	
		}else{
			if(!memcmp(arc[3],"-s",2*sizeof(char))){
				irreduciblePolynomial=convertPolynomialS(arc[4]);
			}else{
				printf("\tERROR %s no es una opcion valida para este tipo de ejecucion (calcular el inverso de cada polinomio en GF(2^%hd), solo se cuenta con las siguientes opciones:\n",arc[2],n);
				printf("\"n\" -h \"polinomio irreducible en formato hexadecimal\" \"archivo a guardar la lista de inversos (no neseariamente deve existir)\"\n");
				printf("\"n\" -d \"polinomio irreducible en formato decimal\" \"archivo a guardar la lista de inversos (no neseariamente deve existir)\"\n");
				printf("\"n\" -s \"polinomio irreducible en formato string\" \"archivo a guardar la lista de inversos (no neseariamente deve existir)\"\n");
				printf("Nota: para el formato string ingresar las potencias con el simbolo \"^\" y si es una potencia 0 poner un uno ejemplo x^5+x^4+x^2+x^1+1\n");
				return;
			}
		}
	}
	printf("n=%hd\tirreduciblePolynomial=%x\tpathFile=%s\n",n,irreduciblePolynomial,pathFile);
	Node *inversesList=inverseEachElementGF2n(n,irreduciblePolynomial);
	saveListInverses(pathFile,inversesList);
	printf("se salvaron los inversos en el archivo %s\n",pathFile);
}
void subtitutionBox(char **arc){
	unsigned char *sb=getSubstitutionBox();
	saveTableSubstitutionBox(arc[2],sb,16,16);
}
void printKeyExpansion(char **arc){
	unsigned char *key=(unsigned char *)malloc(sizeof(unsigned char)*16);
	unsigned int i=0;
	sscanf(strtok(arc[2],"|"),"%x",(unsigned int *)(key+i));
	for(i=1;i<16;i++){
		sscanf(strtok(NULL,"|"),"%x",(unsigned int *)(key+i));
	}
	//printMatrix(key,4,4);
	//printf("\n");
	Node *keys=keyExpansion(key,10);
	unsigned int r,c;
	unsigned char *auxiliary;
	while(keys!=NULL){
	//	printMatrix((unsigned char *)keys->data,4,4);
		auxiliary=(unsigned char *)keys->data;
		for(r=0;r<4;r++){
			for(c=0;c<4;c++){
				printf("%5X",auxiliary[c*4+r]);
			}
			printf("\n");
		}
		printf("\n");
		keys=keys->next;
	}
}
void executionMode(char **arc){
	if(!memcmp(arc[1],"-ip",3*sizeof(char))){
		inversePolynomial(arc);
	}else{
		if(!memcmp(arc[1],"-cs",3*sizeof(char))){
			convertPolynomialToString(arc);	
		}else{
			if(!memcmp(arc[1],"-if",3*sizeof(char))){
				inversesField(arc);	
				}else{
					if(!memcmp(arc[1],"-sb",3*sizeof(char))){
						subtitutionBox(arc);	
						}else{
							if(!memcmp(arc[1],"-ke",3*sizeof(char))){
								printKeyExpansion(arc);	
							}else{
								printf("\tERROR %s no es una opcion!\n opciones de ejecucion:\n",arc[1]);
								printf("para obtener el inverso de un polinomio ejecute como -> %s -ip -h|-d|-s \"polinomio\" \"polinomio irreducible\"\n",arc[0]);
								printf("para convertir un polinomio ingresado en formato de hexadecimal a string-> %s -cs \"polinomio\"\n",arc[0]);
								printf("para obtener el inverso de cada elemento en GF(2^n) -> %s -if \"n\" \"polinomio\" \"polinomio irreducible\" \"nombre del archivo a guardar los inversos\"\n",arc[0]);
								printf("para generar la caja de susbstitucion AES -> %s -sb \"nombre del archivo a guardar la caja\"\n",arc[0]);
								printf("para hacer la expancion de llave -> %s -ke \"llave de 128 bytes en hexadecimal\"\n",arc[0]);
							}
						}
				}
		}
	}
}
int main(int ari,char **arc){
	executionMode(arc);
	return 0;
}
