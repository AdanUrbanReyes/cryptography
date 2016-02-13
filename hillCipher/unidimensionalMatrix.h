#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef __UNIDIMENSIONALMATRIX_H__
#define __UNIDIMENSIONALMATRIX_H__
void printIntegerUnidimensionalMatrix(int *,unsigned int ,unsigned int );
int *getMemoryForIntegerUnidimensionalMatrix(unsigned int ,unsigned int );
int *fillBySTDINIntegerUnidimensionalMatrix(int *,unsigned int ,unsigned int );
int *fillByRandomIntegerUnidimensionalMatrix(int *,unsigned int ,unsigned int ,int ,int );
int *productIntegerUnidimensionalMatrixs(int *,int *,unsigned int ,unsigned int ,unsigned int ,unsigned int );
int *getSubIntegerUnidimensionalMatrixRemovingRowAndColumn(int *,unsigned int ,unsigned int ,unsigned int ,unsigned int );//rtr= row to remove, ctr=column to remove
int determinantIntegerUnidimensionalMatrix(int *,unsigned int ,unsigned int );
short hasInverseIntegerUnidimensionalMatrix(int *,int ,int ,int );
int *attachedIntegerUnidimensionalMatrix(int *,int ,int );
int *transposedIntegerUnidimensionalMatrix(int *,int ,int );
int *inverseIntegerUnidimensionalMatrix(int *,int ,int ,int );
#endif
