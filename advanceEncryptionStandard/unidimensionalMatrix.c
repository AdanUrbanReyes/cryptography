#include "unidimensionalMatrix.h"
void printMatrix(unsigned char *matrix,unsigned int rows,unsigned int columns){
	unsigned int r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			printf("%5X",matrix[r*columns+c]);
		}
		printf("\n");
	}
}
unsigned char *getMemoryForMatrix(unsigned int rows,unsigned int columns){
	size_t size=sizeof(unsigned char)*(rows*columns);
	unsigned char *matrix=(unsigned char *)malloc(size);
	bzero(matrix,size);
	return matrix;
}
