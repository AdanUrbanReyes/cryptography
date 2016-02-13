#include "unidimensionalMatrix.h"
#include "algorithms.h"
void printIntegerUnidimensionalMatrix(int *matrix,unsigned int rows,unsigned int columns){
	unsigned int r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			printf("%3d ",matrix[r*columns+c]);
		}
		printf("\n");
	}
}
int *getMemoryForIntegerUnidimensionalMatrix(unsigned int rows,unsigned int columns){
	size_t size=sizeof(int)*(rows*columns);
	int *matrix=(int *)malloc(size);
	bzero(matrix,size);
	return matrix;
}
int *fillBySTDINIntegerUnidimensionalMatrix(int *matrix,unsigned int rows,unsigned int columns){
	unsigned int r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			printf("[%u][%u] = ",r+1,c+1);
			scanf("%d",matrix+(r*columns+c));
		}
	}
	return matrix;
}
int *fillByRandomIntegerUnidimensionalMatrix(int *matrix,unsigned int rows,unsigned int columns,int lowerRange,int upperRange){
	unsigned int r,c;
	srand(time(NULL));
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			matrix[r*columns+c]=(random()%upperRange)+lowerRange;
		}
	}
	return matrix;
}
int *productIntegerUnidimensionalMatrixs(int *matrix1,int *matrix2,unsigned int rows1,unsigned int columns1,unsigned int rows2,unsigned int columns2){
	if(columns1!=rows2){
			  return NULL;
	}
	int *result=getMemoryForIntegerUnidimensionalMatrix(rows1,columns2);
	unsigned int r1,c1,c2,r2,k=0;
	int auxiliary;
	for(r1=0;r1<rows1;r1++){//shifer rows of matriz one
		for(c2=0;c2<columns2;c2++){//shifer columns of matriz two
			for(auxiliary=0,c1=0,r2=0;c1<columns1&&r2<rows2;c1++,r2++){//shifer columns of matriz one
				auxiliary+=matrix1[(r1*columns1)+c1] * matrix2[(r2*columns2)+c2];
			}
			result[k++]=auxiliary;
		}
	}
	return result;
}
int *getSubIntegerUnidimensionalMatrixRemovingRowAndColumn(int *matrix,unsigned int rows,unsigned int columns,unsigned int rtr,unsigned int ctr){//rtr= row to remove, ctr=column to remove
	if((rows<2 || rtr>rows) || (columns <2 || ctr>columns)){
		return NULL;
	}
	int *subMatrix=getMemoryForIntegerUnidimensionalMatrix(rows-1,columns-1);
	unsigned int r,c,i=0;//rsm = row sub matrix csm = column sub matrix
	for(r=0;r<rows;r++){
		if(r==rtr){//exclulle row entera 
			continue;
		}
		for(c=0;c<columns;c++){
			if(c==ctr){//excluye column entera
				continue;
			}
			subMatrix[i]=matrix[r*columns+c];
			i++;
		}
	}
	return subMatrix;
}
int determinantIntegerUnidimensionalMatrix(int *matrix,unsigned int rows,unsigned int columns){
	if(rows!=columns){
		return 0;
	}
	if(rows==1){
		return matrix[0];
	}
	if(rows==2){//stop recursividad
		return matrix[0]*matrix[3]-matrix[1]*matrix[2];
	}
	int determinant=0;
	int *subMatrix=NULL;
	unsigned int c;
	for(c=0;c<columns;c++){
		subMatrix=getSubIntegerUnidimensionalMatrixRemovingRowAndColumn(matrix,rows,columns,0,c);
		if(c%2==0){
			determinant+=matrix[c]*determinantIntegerUnidimensionalMatrix(subMatrix,rows-1,columns-1);
		}else{
			determinant-=matrix[c]*determinantIntegerUnidimensionalMatrix(subMatrix,rows-1,columns-1);
		}
	}
	return determinant;
}
short hasInverseIntegerUnidimensionalMatrix(int *matrix,int rows,int columns,int lenghtAlphabet){
	//condicion for matrix has inverse greatest common divisor of determinant and lenghtAlphabet tiene que was one, gcd(determinante,lenghtAlphabet)=1
	int determinant=determinantIntegerUnidimensionalMatrix(matrix,rows,columns);
	if(euclides(determinant,lenghtAlphabet)==1){// this is a greatest common divisor if is one then this number(determinant) has inverse in Z/lengthAlphabet, then matrix has inverse
		return 1;
	}
	return 0;//if greatest common divisor is distint of one then this number(determinant) NOT have inverse in Z/lengthAlphabet
}
int *attachedIntegerUnidimensionalMatrix(int *matrix,int rows,int columns){
	if(rows!=columns || rows<2){
		return NULL;
	}
	int *am=getMemoryForIntegerUnidimensionalMatrix(rows,columns);
	int r,c;
	int *sm=NULL;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			sm=getSubIntegerUnidimensionalMatrixRemovingRowAndColumn(matrix,rows,columns,r,c);
			if((r+c)%2==0){
				am[r*columns+c]=determinantIntegerUnidimensionalMatrix(sm,rows-1,columns-1);
			}else{
				am[r*columns+c]=-1*determinantIntegerUnidimensionalMatrix(sm,rows-1,columns-1);
			}
		}
	}
	return am;
}
int *transposedIntegerUnidimensionalMatrix(int *matrix,int rows,int columns){
	int *tm=getMemoryForIntegerUnidimensionalMatrix(columns,rows);//tm = transposed matrix
	int r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			tm[c*rows+r]=matrix[r*columns+c];
		}
	}
	return tm;
}
int *inverseIntegerUnidimensionalMatrix(int *matrix,int rows,int columns,int lenghtAlphabet){//this matrix was in Z/lenghtAlphabet
	if(rows!=columns || rows<2 ){
		return NULL;
	}
	int *im=getMemoryForIntegerUnidimensionalMatrix(rows,columns);//im=inverse matrix this matrix was in Z/lenghtAlphabet
	int determinant=determinantIntegerUnidimensionalMatrix(matrix,rows,columns);
	unsigned int inverseDeterminant=getMultiplicativeInverseUsingExtendedEuclides(determinant,lenghtAlphabet);
	int *toam=transposedIntegerUnidimensionalMatrix(attachedIntegerUnidimensionalMatrix(matrix,rows,columns),rows,columns);//toam= transposedMatrix of attached matrix
	int r,c,temporary;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			temporary=inverseDeterminant*toam[r*columns+c];
			if(temporary<0){
				im[r*columns+c]=lenghtAlphabet-((-1*temporary)%lenghtAlphabet);
			}else{
				im[r*columns+c]=temporary%lenghtAlphabet;
			}
		}
	}
	return im;
}
