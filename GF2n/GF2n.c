//https://community.gns3.com/thread/5506
//http://www.computingforgeeks.com/2015/01/installing-gns3-version-121-on-kali.html
#include "GF2n.h"
unsigned char getDegreePolynomial(unsigned int polynomial){
	unsigned char degree=0;
	while(polynomial>1){
		polynomial>>=1;
		degree++;
	}
	return degree;
}
void printPolynomial(unsigned int polynomial,char variable){
	unsigned char degree=getDegreePolynomial(polynomial);
	unsigned char i=degree+1;//plus one because the variable of polynomial start on second bit example: x^4+x= 10010, varible x start in second bit
	while(i>0){
		if(isTurnedOnBit(polynomial,i)){
			if(i==1){
				printf("1+");
			}else{
				printf("%c^%d+",variable,i-1);
			}
		}
		i--;
	}
	printf("\b ");//for remove last sign +
}
unsigned int multiplyBy2RaisedN(unsigned int ui,unsigned char n){//ui=unsigned int
	return (ui<<n);
}
unsigned char isTurnedOnBit(unsigned int ui,unsigned char position){//i1tbouiop=is 1 the bit of unsigned int on position, ui=unsigned int
	unsigned int auxiliary=1;
	auxiliary<<=(position-1);
	if(ui&auxiliary){
		return 1;
	}
	return 0;
}
unsigned int extract(unsigned int ui,unsigned char sp,unsigned char nb){//ui=unsigned int, sp=start position , nb=number bytes to extract from sp the ui
	unsigned int auxiliary=(pow(2,nb))-1;
	ui>>=sp;
	return (ui&auxiliary);
}
unsigned int invert(unsigned int ui,unsigned char sp,unsigned char nb){//ui=unsigned int, sp=start position , nb=number bytes to extract from sp the ui and invert
	unsigned int auxiliary=(pow(2,nb))-1;
	auxiliary<<=sp;
	return (ui^auxiliary);
}
unsigned int convertStringPolynomialInteger(char *sp){//sp=string polynomial
	unsigned int uip=0;//uip= unsigned int polynomial
	unsigned char exponente;
	char *token=strtok(sp,"+");
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
unsigned int add(unsigned int p,unsigned int q){//p and q are polynomials of GF(2^n)
	return p^q;
}
unsigned int multiply(unsigned int p,unsigned int q,unsigned int m){//p, q and m are polynomials of GF(2^n), m represent an irreducible polynomial of degree n
	unsigned char i,degree=getDegreePolynomial(m);
	unsigned int result=0,auxiliary=q,mask=pow(2,degree)-1;
	for(i=1;i<=degree;i++){
		if(isTurnedOnBit(p,i)){
			result=add(result,auxiliary);	
		}
		auxiliary<<=1;
		if(getDegreePolynomial(auxiliary)>=degree){
			auxiliary&=mask;
			auxiliary=add(auxiliary,m&mask);
		}
	}
	return result;
}
