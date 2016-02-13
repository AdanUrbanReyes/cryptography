#include <stdio.h>
#include "modularArithmetic.h"
void setIntegerBySTDIN(int *i,char *message){
	if(message==NULL){
		printf("ingrese un entero: ");
	}else{
		printf("%s: ",message);
	}
	scanf("%d",i);
}
void setUnsignedIntegerBySTDIN(unsigned int *ui,char *message){
	if(message==NULL){
		printf("ingrese un entero sin signo (solo positivos): ");
	}else{
		printf("%s: ",message);
	}
	scanf("%u",ui);
}
int main(void){
	short option;
	int a,b;
	unsigned int n;//module
	
//	while(EXPRECION VOLEANA VERDADERO O FALSO) no se save cuantas iteraciones va hacer 
//	for(INICIALIZAN VAIABLES;EXPRECION VOLEANEA;CAMBIAN LAS VARIABLES) se utiliza cuando se save cuantas iteraciones se va a ser
//	do{}while();//no se save cuantas iteraciones se aran pero el codigo dentro del do se ejecutara almenos una ves
/*
	tipo de dato		forma de leer del teclado		memoria que ocupa			representacion
	int					%d											4bytes=32bits				-2^31-1 --> +2^31-1
	char					%c											1bytes=8bits				-2^7-1 ---> +2^7-1
	double				%e o %f									8bytes=64bits				
	float					%f											4bytes
	short					%hd										2bytes=16bits						-2^15 --> +2^15
	
	unsigned int
	unsigned char
	unsigned double
	unsignd float
	unsigned shor
*/
	do{
		printf("\t\t\tingrese una opcion\n\t1. (a+b)mod(n)\n\t2. (a-b)mod(n)\n\t3. (a*b)mod(n) \n\t4. inverso aditivo\n\t5. inverso multiplicativo\n\t-1. para salir\n");
		scanf("%hd",&option);
		switch(option){
			case 1:
				setIntegerBySTDIN(&a,"igrese el valor para a");
				setIntegerBySTDIN(&b,"igrese el valor para b");
				setUnsignedIntegerBySTDIN(&n,"igrese el valor para modulo");
				printf("(%d+%d)modulo(%u) = %u\n",a,b,n,modularAdd(a,b,n));
			break;
			case 2: 
				setIntegerBySTDIN(&a,"igrese el valor para a");
				setIntegerBySTDIN(&b,"igrese el valor para b");
				setUnsignedIntegerBySTDIN(&n,"igrese el valor para modulo");
				printf("(%d-%d)modulo(%u) = %u\n",a,b,n,modularSubtraction(a,b,n));
			break;
			case 3:
				setIntegerBySTDIN(&a,"igrese el valor para a");
				setIntegerBySTDIN(&b,"igrese el valor para b");
				setUnsignedIntegerBySTDIN(&n,"igrese el valor para modulo");
				printf("(%d*%d)modulo(%u) = %u\n",a,b,n,modularMultiplicative(a,b,n));
			break;
			case 4: 
				setIntegerBySTDIN(&a,"igrese el valor para a");
				setUnsignedIntegerBySTDIN(&n,"igrese el valor para modulo");
				printf("el inverso aditivo de %d en Z/%u es: %u\n",a,n,additiveInverse(a,n));
			break;
			case 5: 
				setUnsignedIntegerBySTDIN((unsigned int *)&a,"igrese el valor para a");
				setUnsignedIntegerBySTDIN(&n,"igrese el valor para b");
				b=multiplicativeInverse((unsigned int)a,n);
				if(b<1){
					printf("|%d| NO TIENE inverso multiplicativo en %u\n",a,n);
				}else{
					printf("el inverso multiplicativo de %d en Z/%u es: %u\n",a,n,b);
				}
			break;
			case -1: 
				printf("Asta pronto :D\n");
			break;
			default: printf("ERROR %hd no es una opcion! \n",option);break;
		}
	}while(option!=-1);	
	return 0;
}
