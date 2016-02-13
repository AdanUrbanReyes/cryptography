#include "rivestShamirAdleman.h"
#include "list.h"
unsigned int powerModule(unsigned int base,unsigned int exponent, unsigned int module){
	unsigned int result=1;
	for(;e>0;e--){
		result*=base;
		result%=module;
	}
	return result;
}
unsigned int *getNextGenerator(unsigned int primeNumber,unsigned int *generator){
	if(generator==NULL){
		generator=(unsigned int *)malloc(sizeof(unsigned int));
		*generator=2;
	}
	List resultPowerModule;
	while(){
		while(){
					
		}
	}
	return generator;
}
