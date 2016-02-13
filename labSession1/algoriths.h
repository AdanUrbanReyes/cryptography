#include <stdio.h>
#include <stdlib.h>
#include "unidimensionalArray.h"
#ifndef __ALGORITHS_H__
#define __ALGORITHS_H__
void printMatrizUnidimensionalLikeMatriz(int *matriz,int rows,int columns){
	unsigned int r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			printf("%3d ",matriz[r*columns+c]);
		}
		printf("\n");
	}
	printf("\n");
}
int *setIntegerValueForMatrizUnidimensional(int *matriz,unsigned int i,unsigned int j,unsigned int columns,int value){
	i--;
	j--;
	matriz[(i*columns)+j]=value;
	return matriz;
}
int getIntegerValueForMatrizUnidimensional(int *matriz,unsigned int i,unsigned int j,unsigned int columns){
	i--;
	j--;
	return matriz[(i*columns)+j];
}
int **getIntegerMatrizesUnidimensionales(unsigned int numberMatrizes,unsigned int rows,unsigned int columns){
	int **matrizes=(int **)malloc(sizeof(int *)*(numberMatrizes));
	int i;
	for(i=0;i<numberMatrizes;i++){
		matrizes[i]=getIntegerArrayMemoryForMatriz(rows,columns);
	}
	return matrizes;
}

int *multiplicaMatrizesUnidimensionales(int *matrizOne,int *matrizTwo,unsigned int rowsOne,unsigned int columnsOne,unsigned int rowsTwo,unsigned int columnsTwo){
	if(columnsOne!=rowsTwo){
		return NULL;
	}
	int *result=(int *)malloc(sizeof(int)*(rowsOne*columnsTwo));
	unsigned int ro,co,rt,ct,k=0;
	int auxiliary;
	for(ro=0;ro<rowsOne;ro++){//shifer rows of matriz one
		for(ct=0;ct<columnsTwo;ct++){//shifer columns of matriz two
			for(auxiliary=0,co=0,rt=0;co<columnsOne&&rt<rowsTwo;co++,rt++){//shifer columns of matriz one
				auxiliary+=matrizOne[(ro*columnsOne)+co] * matrizTwo[(rt*columnsTwo)+ct];
			}
			result[k++]=auxiliary;
		}
	}
	return result;
}
#endif
