#include "modularArithmetic.h"
#include <stdio.h>
unsigned int modularAdd(int a,int b,unsigned int n){
	if(n<2){
		return 0;
	}
	int add=a+b;
	if(add<0){
		return (n-(abs(add)%n));
	}
	return add%n;
}
unsigned int modularSubtraction(int a,int b,unsigned int n){
	if(n<2){
		return 0;
	}
	int substraction=a-b;
	if(substraction<0){
		return (n-(abs(substraction)%n));
	}
	return substraction%n;
}
unsigned int modularMultiplicative(int a,int b,unsigned int n){
	if(n<2){
		return 0;
	}
	int multiplicative=a*b;
	if(multiplicative<0){
		return (n-(abs(multiplicative)%n));
	}
	return multiplicative%n;
}
unsigned int additiveInverse(int a, unsigned int n){
	int substraction=n-a;
	if(substraction<0){
		return (n-(abs(substraction)%n));
	} 
	return substraction;
}
int multiplicativeInverse(unsigned int a, unsigned int b){
	int u=a,v=b;
	unsigned char flag=0;
	if(a<b){
		flag=1;
		u=a;
		a=b;
		b=u;
	}
	//v=a,u=b;
	v=b,u=a;
	int x1=1,y1=0,x2=0,y2=1;
	int q,r;
	int *result=(int *)malloc(sizeof(int)*3);//x=[0], y=[1] y d=[2] estan aki 
//	int i=1;
	while(u!=0){
	//	printf("iteracion %d\n",i);
	//	printf("\tu=%d|v=%d|q=%d,r=%d|x1=%d|x2=%d|y1=%d|y2=%d|x=%d,y=%d\n",u,v,q,r,x1,x2,y1,y2,result[0],result[1]);	
		q=v/u;
		r=v-q*u;
		result[0]=x2-q*x1;
		result[1]=y2-q*y1;
		v=u;
		u=r;
		x2=x1;
		x1=result[0];
		y2=y1;
		y1=result[1];
	//	printf("\tu=%d|v=%d|q=%d,r=%d|x1=%d|x2=%d|y1=%d|y2=%d|x=%d,y=%d\n",u,v,q,r,x1,x2,y1,y2,result[0],result[1]);	
		
	}
	result[2]=v;
	result[0]=x2;
	result[1]=y2;
	if(result[0]<0){
		result[0]=b-(abs(result[0])%b);
	}
	if(result[1]<0){
		result[1]=a-(abs(result[1])%a);
	}
	//printf("x=%d,y=%d,d=%d\n",result[0],result[1],result[2]);
	if(flag==0)
		return result[0];
	return (result[1]);
}
