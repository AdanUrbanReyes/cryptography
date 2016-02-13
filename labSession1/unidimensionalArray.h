#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __UNIDIMENSIONALARRAY_H__
#define __UNIDIMENSIONALARRAY_H__
void printIntegerArray(int *array,size_t sizeofArray){
	size_t i;
	for(i=0;i<sizeofArray;i++){
		printf("{%d,",array[i]);
	}
	printf("\b}\n");
}
int *getIntegerArrayMemoryForMatriz(unsigned int rows,unsigned int columns){
	int *array=(int *)malloc(sizeof(int)*(rows*columns));
	return array;
}
int *fillBySTDINIntegerArray(int *array,unsigned int lenghtArray){
	unsigned int i;
	printf("ingrese los valores enteros para el arreglo.\n");
	for(i=0;i<lenghtArray;i++){
		printf("[%d] = ",i);
		scanf("%d",array+i);
	}
	return array;
}
int *fillByRandomIntegerArray(int *array,unsigned int lenghtArray,int lowerRange,int upperRange){
	unsigned int i;
	srand(time(NULL));
	for(i=0;i<lenghtArray;i++){
		array[i]=(random()%upperRange)+lowerRange;
	}
	return array;
}
#endif
