#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "unidimensionalArray.h"
#include "algoriths.h"
/*
	compila as gcc main.c -o main -Wall -Werror
	for run program ./main
*/
void exerciseOne(int **matriz,unsigned int *rows,unsigned int *columns){
	printf("ingrese el numero de filas\n");
	scanf("%u",rows);
	printf("ingrese el numero de columnas\n");
	scanf("%u",columns);
	*matriz=getIntegerArrayMemoryForMatriz(*rows,*columns);
	bzero(*matriz,sizeof(int)*((*rows) * (*columns)));
	if(*matriz==NULL){
		printf("no ahy mas memoria\n");
	}else{
		printf("matriz con %u filas %u columnas creada (vacia con ceros)\n",*rows,*columns);
	}
}
void exerciseTwo(int **matriz,unsigned int leghtMatriz,char flag){
	if(*matriz==NULL){
		printf("primero inicialice la matriz con la opcion 1\n");
	}else{
		if(flag==1){//fill with random
			fillByRandomIntegerArray(*matriz,leghtMatriz,0,10);
		}else{
			fillBySTDINIntegerArray(*matriz,leghtMatriz);
		}
	}
}
void exerciseThree(int **matriz,int columns){
	if(*matriz==NULL){
		printf("primero inicialice la matriz con la opcion 1\n");
		return ;
	}
	unsigned int row,column;
	int value;
	printf("ingrese la fila: ");
	scanf("%u",&row);
	printf("ingrese la columna: ");
	scanf("%u",&column);
	printf("ingrese el valor a poner: ");
	scanf("%d",&value);
	setIntegerValueForMatrizUnidimensional(*matriz,row,column,columns,value);
}
void exerciseFour(int **matriz,int columns){
	if(*matriz==NULL){
		printf("primero inicialice la matriz con la opcion 1\n");
		return ;
	}
	unsigned int row,column;
	printf("ingrese la fila: ");
	scanf("%u",&row);
	printf("ingrese la columna: ");
	scanf("%u",&column);
	printf("valor de la matriz en fila %d, colupna %d = %d\n",row,column,getIntegerValueForMatrizUnidimensional(*matriz,row,column,columns));
}
void exerciseFive(){
	unsigned int i,numberMatrizes,row,column;
	int **matrizes=NULL;
	printf("ingrese el numero de matrizes a crear: ");
	scanf("%u",&numberMatrizes);
	printf("ingrese numero de filas para todas las matrizes: ");
	scanf("%u",&row);
	printf("ingrese numero de columnas para todas las matrizes: ");
	scanf("%u",&column);
	matrizes=getIntegerMatrizesUnidimensionales(numberMatrizes,row,column);
	for(i=0;i<numberMatrizes;i++){
		fillByRandomIntegerArray(matrizes[i],(row*column),0,10);
		printf("matriz %d creada con numeros aleatorios:\n",i+1);
		printMatrizUnidimensionalLikeMatriz(matrizes[i],row,column);
	}
}
void exerciseSix(){
	int **matrizes=(int **)malloc(sizeof(int *)*2);
	int *result=NULL;
	unsigned int rmo,cmo,rmt,cmt;//rm = rows for matriz, cm = columns for matriz , one two
	printf("ingrese numero de filas para la primera matriz: ");
	scanf("%u",&rmo);
	printf("ingrese numero de columnas para la primera matriz: ");
	scanf("%u",&cmo);
	printf("ingrese numero de filas para la segunda matriz: ");
	scanf("%u",&rmt);
	printf("ingrese numero de columnas para la segunda matriz: ");
	scanf("%u",&cmt);
	if(cmo!=rmt){
		printf("para multiplicar dos matrizes el numero de columnas de la primara matriz deve ser igual al numero de filas de la segunda matriz!");
		return;
	}
	matrizes[0]=getIntegerArrayMemoryForMatriz(rmo,cmo);
	matrizes[1]=getIntegerArrayMemoryForMatriz(rmt,cmt);
	fillBySTDINIntegerArray(matrizes[0],rmo*cmo);
	fillBySTDINIntegerArray(matrizes[1],rmt*cmt);
	result=multiplicaMatrizesUnidimensionales(matrizes[0],matrizes[1],rmo,cmo,rmt,cmt);
	printMatrizUnidimensionalLikeMatriz(matrizes[0],rmo,cmo);
	printf("\t\t\t\nmultiplicada por\n");
	printMatrizUnidimensionalLikeMatriz(matrizes[0],rmo,cmo);
	printMatrizUnidimensionalLikeMatriz(result,rmo,cmt);
}
int main(void){
	int *matriz=NULL;
	int option;
	unsigned int rowsMatriz=0,columnsMatriz=0;
	do{
		getchar();
		getchar();
		system("clear");
		printf("\t\t\tingrese una opcion o -1 para salir\n\t1.crear matriz unidimencional\n\t2.llenar matriz unidimencional con valores introducidos\n\t3.llenar matriz unidimencional con valores aleatorios\n\t4.poner un valor en una pocicion de la matriz unidimencional\n\t5.obtener el valor en una pocicion de la matriz unidimencional\n\t6.obtener un arreglo de matrizes unidimencionales\n\t7.multiplicacion de dos matrizes unidimensionales\n\t8. imprimir matriz\n");
		scanf("%d",&option);
		switch(option){
			case 1: 
				exerciseOne(&matriz,&rowsMatriz,&columnsMatriz);
			break;
			case 2:
				exerciseTwo(&matriz,(rowsMatriz*columnsMatriz),0);
			break;
			case 3:
				exerciseTwo(&matriz,(rowsMatriz*columnsMatriz),1);
			break;
			case 4:
				exerciseThree(&matriz,columnsMatriz);
			break;
			case 5:
				exerciseFour(&matriz,columnsMatriz);
			break;
			case 6: 
				exerciseFive();
			break;
			case 7:
				exerciseSix();
			break;
			case 8:
				printMatrizUnidimensionalLikeMatriz(matriz,rowsMatriz,columnsMatriz);
			break;
			case -1: printf("hasta pronto :D\n"); break;
			default: printf("la opcion %d no existe!\n",option);
		}
	}while(option!=-1);
	return 0;
}
