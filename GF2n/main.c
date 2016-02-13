#include <stdio.h>
#include <stdlib.h>
#include "GF2n.h"
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
	unsigned int x,sp,nb;
	char *p=NULL,*q=NULL,*m=NULL;
	do{
		printf("\n\tElija una opcion\n\t1 Multiplicar numero entero por 2^n\n\t2 Es 1 el bit en la posicion \"p\"\n\t3 Extraer \"n\" bits apartir de la posicion \"p\" del entero\n\t4 Extraer \"n\" bits apartir de la posicion \"p\" del entero y negarlos\n\t5 Sumar GF(2^n)\n\t6 Multiplicacion GF(2^n)\n\t-1 Salir\n");
		scanf("%hd",&option);
		switch(option){
			case 1:
				setUnsignedIntegerBySTDIN(&x,NULL);
				setUnsignedIntegerBySTDIN(&sp,"ingrese el valor de n");
				printf("%u*2^%u=%u",x,sp,multiplyBy2RaisedN(x,sp));	
			break;
			case 2:
				setUnsignedIntegerBySTDIN(&x,NULL);
				setUnsignedIntegerBySTDIN(&sp,"ingrese la posicion (entre 1 y 32)");
				printf("el bit %u del entero %u es=%hd",sp,x,isTurnedOnBit(x,(unsigned char)sp));
			break;
			case 3:
				setUnsignedIntegerBySTDIN(&x,NULL);
				setUnsignedIntegerBySTDIN(&sp,"ingrese la posicion inicial (entre 1 y 32)");
				setUnsignedIntegerBySTDIN(&nb,"ingrese el numero de bits a extraer (entre 1 y 32, tomando en cuenta la posicion inicial)");
				printf("%u = %u extraido %u apartir del bit %u",extract(x,(unsigned char)sp,(unsigned char)nb),x,nb,sp);
			break;
			case 4:
				setUnsignedIntegerBySTDIN(&x,NULL);
				setUnsignedIntegerBySTDIN(&sp,"ingrese la posicion inicial (entre 1 y 32)");
				setUnsignedIntegerBySTDIN(&nb,"ingrese el numero de bits a extraer y negar (entre 1 y 32, tomando en cuenta la posicion inicial)");
				printf("%u = %u extraido %u y negado apartir del bit %u",invert(x,(unsigned char)sp,(unsigned char)nb),x,nb,sp);
			break;
			case 5:
				p=(char *)malloc(sizeof(char)*MSOPS);
				q=(char *)malloc(sizeof(char)*MSOPS);
				printf("ingrese polinomios a sumar en GF(2^n), el formato es x^n+x^n-1+...+x^1+1, ejemplos: x^4+x^1+1, x, x^3+x^1, x^1+1...\n");
				printf("primer polinomio: ");
				scanf("%s",p);
				printf("segundo polinomio:");
				scanf("%s",q);
				sp=convertStringPolynomialInteger(p);	
				nb=convertStringPolynomialInteger(q);
				printPolynomial(sp,'x');
				printf(" + ");
				printPolynomial(nb,'x');
				printf(" = ");
				printPolynomial(add(sp,nb),'x');
			break;
			case 6:
				p=(char *)malloc(sizeof(char)*MSOPS);
				q=(char *)malloc(sizeof(char)*MSOPS);
				m=(char *)malloc(sizeof(char)*MSOPS);
				printf("ingrese polinomios a multiplicar en GF(2^n), el formato es x^n+x^n-1+...+x^1+1, ejemplos: x^4+x^1+1, x, x^3+x^1, x^1+1...\n");
				printf("primer polinomio: ");
				scanf("%s",p);
				printf("segundo polinomio: ");
				scanf("%s",q);
				printf("polinomio irreducible: ");
				scanf("%s",m);
				sp=convertStringPolynomialInteger(p);	
				nb=convertStringPolynomialInteger(q);
				x=convertStringPolynomialInteger(m);
				printPolynomial(sp,'x');
				printf(" * ");
				printPolynomial(nb,'x');
				printf("modulo( ");
				printPolynomial(x,'x');
				printf(" ) = ");
				printPolynomial(multiply(sp,nb,x),'x');
			break;
			case -1:
				printf("\tasta pronto :D\n");
			break;
			default:
				printf("\tERROR %hd no es una opcion!\n",option);
			break;
		}
	}while(option!=-1);
	return 0;
}
