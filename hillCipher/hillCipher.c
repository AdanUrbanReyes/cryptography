#include "hillCipher.h"
/*
	A-Z 65-90
	a-z 97-122
	A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
	0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
*/
unsigned int *applyModuleToArray(int *array,unsigned int lenght,unsigned int module){//lenght is of array module is module to apply for all array
	unsigned int i;
	for(i=0;i<lenght;i++){
		if(array[i]<0){
			array[i]=module-((array[i]*-1)%module);
		}else{
			array[i]%=module;
		}
	}
	return (unsigned int *)array;
}
char *arrayIntegersToArrayAlphabet(int *integers,unsigned int lenghtIntegers){
	char *alphabet=(char *)malloc(sizeof(char)*lenghtIntegers);
	unsigned int i;
	for(i=0;i<lenghtIntegers;i++){
		alphabet[i]=integers[i]+AUCA;
	}
	return alphabet;
}
short encryptFileWithHillCipher(char *pathInFile,int *key,unsigned int rows,unsigned int columns,char *pathOutFile){//rows and columns is for key matrix
	if(rows!=columns){//is because key needed squared matrix
		return -1;
	}
	int dif=open(pathInFile,O_RDONLY);//descriptor in file
	int dof=open(pathOutFile,O_WRONLY|O_CREAT,0666);//descriptor out file
	if(dif<0 || dof<0){//culdent open files
		return -3;
	}
	char buffer;//buffer is same a character readed del file	
	int *ptmtn=getMemoryForIntegerUnidimensionalMatrix(1,columns);//ptmtn=plain text mapeado to numbers
	unsigned char flag=0;//this is for know when read a number of characteres de acuerdo con rows or columns of key	
	while((read(dif,&buffer,sizeof(char)))>0){	
		if(isalpha(buffer)){//if character readed is alphabet (A-Z) or a-z
			if(islower(buffer)){//if is lower case (a-z)
				ptmtn[flag]=buffer-ALCA;//this "mapea" codigo ascii of letter to 0-25 example if buffer containes d = 100 on code asicc then ptmt[]=100-97=3
			}else{//then was upper case (A-Z)
				ptmtn[flag]=buffer-AUCA;//this "mapea" codigo ascii of letter to 0 -25 example if buffer contains B = 66 on code assic then ptmt[]=66-65 = 1
			}
			flag++;
		}
		if(flag==rows){//then mm is filled
			flag=0;
			ptmtn=(int *)applyModuleToArray(productIntegerUnidimensionalMatrixs(ptmtn,key,1,columns,rows,columns),columns,LA);//ptmtn containts product and module
			write(dof,arrayIntegersToArrayAlphabet(ptmtn,columns),sizeof(char)*rows);
		}
	}
	if(flag!=0){
		srand(time(NULL));
		while(flag!=rows){
			ptmtn[flag]=random()%25;
			flag++;
		}
		ptmtn=(int *)applyModuleToArray(productIntegerUnidimensionalMatrixs(ptmtn,key,1,columns,rows,columns),columns,LA);//ptmtn containts product and module
		write(dof,arrayIntegersToArrayAlphabet(ptmtn,columns),sizeof(char)*rows);
	}
	close(dif);
	close(dof);
	return 0;
}
short descryptFileWithHillCipher(char *pathInFile,int *key,unsigned int rows,unsigned int columns,char *pathOutFile){	
	if(rows!=columns){//is because key needed squared matrix
		return -1;
	}
	int dif=open(pathInFile,O_RDONLY);//descriptor in file
	int dof=open(pathOutFile,O_WRONLY|O_CREAT,0666);//descriptor out file
	if(dif<0 || dof<0){//culdent open files
		return -3;
	}
	key=inverseIntegerUnidimensionalMatrix(key,rows,columns,LA);//key now is inverse of key
	char buffer;//buffer is same a character readed del file	
	int *ptmtn=getMemoryForIntegerUnidimensionalMatrix(1,columns);//ptmtn=plain text mapeado to numbers
	unsigned char flag=0;//this is for know when read a number of characteres de acuerdo con rows or columns of key	
	while((read(dif,&buffer,sizeof(char)))>0){	
		if(isalpha(buffer)){//if character readed is alphabet (A-Z) or a-z
			if(islower(buffer)){//if is lower case (a-z)
				ptmtn[flag]=buffer-ALCA;//this "mapea" codigo ascii of letter to 0-25 example if buffer containes d = 100 on code asicc then ptmt[]=100-97=3
			}else{//then was upper case (A-Z)
				ptmtn[flag]=buffer-AUCA;//this "mapea" codigo ascii of letter to 0 -25 example if buffer contains B = 66 on code assic then ptmt[]=66-65 = 1
			}
			flag++;
		}
		if(flag==rows){//then mm is filled
			flag=0;
			ptmtn=(int *)applyModuleToArray(productIntegerUnidimensionalMatrixs(ptmtn,key,1,columns,rows,columns),columns,LA);//ptmtn containts product and module
			write(dof,arrayIntegersToArrayAlphabet(ptmtn,columns),sizeof(char)*rows);
		}
	}
	close(dif);
	close(dof);
	return 0;	
}
