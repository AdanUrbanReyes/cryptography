#include "algorithms.h"
unsigned int euclides(unsigned int x,unsigned int y){//this function return greatest common divisor
	unsigned int remainderOld=y,remainderCurrent=x%y;
	if(y>x){
		remainderOld=x;
	}
	while(remainderCurrent!=0){
		remainderOld=remainderCurrent;
//		printf("%u = %u*%u+%u\n",x,y,x/y,remainderCurrent);
		remainderCurrent=y%remainderOld;
		y=remainderOld;
	}
	return remainderOld;//this is a grates common devicer
}
int *extendedEuclides(unsigned int x, unsigned int y){//this function return array that contain multiplicative inverse of x in Z/y and viseversa multiplicative inverse of y in Z/x	
	int quotient=x/y;
	unsigned int remainder=x%y;
	int *last=(int *)malloc(sizeof(int)*4);//here was exprecion of inverse multiplicative (1=ax+by, where a is inverse multiplicative of x in Z/y and b is inverse multiplicative of y in Z/x)
	if(remainder==1){
		last[0]=x;
		last[1]=1;
		last[2]=y;
		last[3]=-1*quotient;
		return last;
	}
	last=extendedEuclides(y,remainder);
	int auxiliary;
	last[0]=x;
	auxiliary=last[1];
	last[1]=last[3];
	last[2]=y;
	last[3]=last[3]*-1*quotient+auxiliary;
	return last;
}
unsigned int getMultiplicativeInverseUsingExtendedEuclides(unsigned int x,unsigned int y){
	int *ee=extendedEuclides(x,y);
	if(ee[1]<0){
		return y-((ee[1]*-1)%y);	
	}
	return (ee[1]%y);
}
