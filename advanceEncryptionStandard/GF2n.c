#include "GF2n.h"
#include <stdio.h>
void exchangeValuesUC(unsigned char *v1,unsigned char *v2){
	unsigned char auxiliary=*v1;
	*v1=*v2;
	*v2=auxiliary;
}
void exchangeValues(unsigned int *v1,unsigned int *v2){
	unsigned int auxiliary=*v1;
	*v1=*v2;
	*v2=auxiliary;
}
unsigned char getDegreePolynomial(unsigned int polynomial){
	unsigned char degree=0;
	while(polynomial>1){
		polynomial>>=1;
		degree++;
	}
	return degree;
}
unsigned char isTurnedOnBit(unsigned int ui,unsigned char position){
	if(position>32){
		return 0;
	}
	unsigned int auxiliary=1;
	auxiliary<<=position;
	if(ui&auxiliary){
		return 1;
	}
	return 0;
}
unsigned int convertPolynomialS(char *polynomial){
	unsigned int uip=0;//uip= unsigned int polynomial
	unsigned char exponente;
	char *token=strtok(polynomial,"+");
	while(token!=NULL){
		if(strchr(token,'^')==NULL){
			exponente=0;
		}else{
			sscanf(token,"x^%d",(int *)&exponente);	
		}
		uip+=pow(2,exponente);
		token=strtok(NULL,"+");
	}
	return uip;
}
char *convertPolynomialUI(unsigned int polynomial,char variable){
	char *sp=(char *)malloc(sizeof(char));//sp=string polynomial
	unsigned char degree=0;
	size_t lenght=0;
	while(polynomial>0){
		lenght=strlen(sp);
		if(isTurnedOnBit(polynomial,0)){
			if(degree==0){
				sp=(char *)realloc((void *)sp,sizeof(char)*(lenght+3));
				bzero(sp+lenght,sizeof(char)*3);
				strcat(sp,"1+");
			}else{
				sp=(char*)realloc((void *)sp,sizeof(char)*(lenght+6));
				bzero(sp+lenght,sizeof(char)*6);
				sprintf(sp+lenght,"%c^%hd+",variable,degree);
			}
		}
		polynomial>>=1;
		degree++;
	}
	sp[strlen(sp)-1]=0;
	return sp;
}
unsigned int modulePolynomial(unsigned int polynomial,unsigned int module){
	unsigned char degreeModule=getDegreePolynomial(module);
	unsigned char differenceBetweenDegrees;
	while((differenceBetweenDegrees=getDegreePolynomial(polynomial))>=degreeModule){
		differenceBetweenDegrees-=degreeModule;
		polynomial=polynomial^(module<<differenceBetweenDegrees);//here apply formule r(x)=polynomial + (x^differenceBetweenDegrees * m(x))
	}
	return polynomial;
}
unsigned int multiply(unsigned int p,unsigned int q,unsigned int module){//p, q and m are polynomials of GF(2^n), m represent an irreducible polynomial of degree n
	unsigned int result=0;
	unsigned char degreeP=0;
	if(p>q){//this is for make less iterations
		exchangeValues(&p,&q);
	}
	while(p>0){
		if(isTurnedOnBit(p,0)){
			result=result ^ modulePolynomial( ( q<<degreeP ) , module );
		}
		p>>=1;
		degreeP++;
	}
	return result;
}
unsigned int extendedEuclides(unsigned int polynomial,unsigned int irreduciblePolynomial){
	unsigned int u=polynomial, v=irreduciblePolynomial, g1=1, g2=0;
	short differenceBetweenDegrees=0;
	while(u!=1){
		differenceBetweenDegrees=getDegreePolynomial(u)-getDegreePolynomial(v);
		if(differenceBetweenDegrees<0){
			exchangeValues(&u,&v);
			exchangeValues(&g1,&g2);
			differenceBetweenDegrees*=-1;
		}
		u=u ^ (v << differenceBetweenDegrees);
		g1=g1 ^ (g2 << differenceBetweenDegrees);
	}
	return g1;
}
/*start eracer */
char saveListInverses(char *pathFile,Node *head){
	if(head==NULL){
		return 1;
	}
	int descriptor=open(pathFile,O_WRONLY|O_CREAT,0666);
	if(descriptor<0){
		return 2;
	}
	size_t size=sizeof(char)*13;
	char *auxiliary=(char *)malloc(size);
	while(head!=NULL){
		sprintf(auxiliary,"%6X%6X\n",((unsigned int *)head->data)[0],((unsigned int*)head->data)[1]);
		write(descriptor,(void *)auxiliary,size);
		head=head->next;
	}
	close(descriptor);
	return 0;
}
unsigned int *getCopyPolynomialAndHisInverse(unsigned int polynomial, unsigned int inverse){
	unsigned int *polynomialAndHisInverse=(unsigned int *)malloc(sizeof(unsigned int)*2);
	polynomialAndHisInverse[0]=polynomial;
	polynomialAndHisInverse[1]=inverse;
	return polynomialAndHisInverse;
}
Node *inverseEachElementGF2n(unsigned char n,unsigned int irreduciblePolynomial){
	if(n>32){
		return NULL;
	}
	unsigned int polynomial=1;
	unsigned int tope=pow(2,n)-1;
	Node *head=NULL;
	addNode(&head,getNode(getCopyPolynomialAndHisInverse(0,0),NULL,NULL));
	for(polynomial=1;polynomial<=tope;polynomial++){
		addNode(&head,getNode(getCopyPolynomialAndHisInverse(polynomial,extendedEuclides(polynomial,irreduciblePolynomial)),NULL,NULL));
	}
	return head;
}
/*end eracer*/
