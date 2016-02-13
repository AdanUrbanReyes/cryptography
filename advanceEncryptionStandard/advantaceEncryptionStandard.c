#include "advantaceEncryptionStandard.h"
#include "list.h"
unsigned char *getSubstitutionBox(){
	unsigned short rowColumn=1;
	unsigned char *substitutionBox=getMemoryForMatrix(16,16);
	substitutionBox[0]=SFA;
	for(rowColumn=1;rowColumn<=255;rowColumn++){
		substitutionBox[rowColumn]=multiply(extendedEuclides(rowColumn,IP),STM ,MSTM) ^ SFA;
	}
	return substitutionBox;
}

unsigned char *shiftUp(unsigned char *w){
	exchangeValuesUC(&w[0],&w[3]);
	exchangeValuesUC(&w[0],&w[2]);
	exchangeValuesUC(&w[0],&w[1]);
	return w;
}
unsigned char *exchangeBySubstitutionBox(unsigned char *w,unsigned char *substitutionBox){
	unsigned char row,column,i;
	for(i=0;i<4;i++){
		row=(w[i]&0xF0)>>4;
		column=w[i]&0x0F;
		//printf("exchangeBySubstitutionBox row=%x,column=%x\n",row,column);
		w[i]=substitutionBox[row*16+column];
	}
	return w;
}
unsigned char getCi(unsigned char numberRound,unsigned int irreduciblePolynomial){
	unsigned char x=1;
	x<<=(numberRound-1);
	x=(unsigned char )modulePolynomial(x,irreduciblePolynomial);
	return x;
}
Node *keyExpansion(unsigned char *key,unsigned char numberRounds){
	unsigned char nr,r,c;

	Node *keys=NULL;
	unsigned char *w=(unsigned char *)malloc(sizeof(unsigned char)*4);
	unsigned char *substitutionBox=getSubstitutionBox();
	memcpy(w,key+12,sizeof(char)*4);
	//printf("start w=%x|%x|%x|%x\n",w[0],w[1],w[2],w[3]);
	addNode(&keys,getNode((void *)key,NULL,NULL));
	for(nr=1;nr<=numberRounds;nr++){
		w=shiftUp(w);
		//printf("w shift = %x|%x|%x|%x\n",w[0],w[1],w[2],w[3]);
		w=exchangeBySubstitutionBox(w,substitutionBox);	
		//printf("w exchange substitutionBox = %x|%x|%x|%x\n",w[0],w[1],w[2],w[3]);
		w[0]=w[0]^getCi(nr,IP);
		//printf("w[0]^ci = %x|%x|%x|%x\n",w[0],w[1],w[2],w[3]);
		unsigned char *keyRound=(unsigned char *)malloc(sizeof(unsigned char)*4);
		unsigned char *keyRound_1=(unsigned char *)(getNodeByPosition(keys,nr-1)->data);
		for(r=0;r<4;r++){
			for(c=0;c<4;c++){
				w[c]=w[c]^keyRound_1[r*4+c];
				keyRound[r*4+c]=w[c];
			}
			//printf("kr[%hd] = %x|%x|%x|%x\n",r,keyRound[r*4],keyRound[r*4+1],keyRound[r*4+2],keyRound[r*4+3]);
		}
		//printf("w[0] end rc  = %x|%x|%x|%x\n",w[0],w[1],w[2],w[3]);
		addNode(&keys,getNode((void* )keyRound,NULL,NULL));
	}
	return keys;
}

/*eracer code*/
char saveTableSubstitutionBox(char *pathFile,unsigned char *table,unsigned int rows,unsigned char columns){
	if(table==NULL){
		return 1;
	}
	int descriptor=open(pathFile,O_WRONLY|O_CREAT,0666);
	if(descriptor<0){
		return 2;
	}
	size_t size=sizeof(char)*4;
	char *auxiliary=(char *)malloc(size);
	unsigned char r,c;
	for(r=0;r<rows;r++){
		for(c=0;c<columns;c++){
			sprintf(auxiliary,"%4x",table[r*columns+c]);
			write(descriptor,(void *)auxiliary,size);
		}
		strcpy(auxiliary,"\n");
		write(descriptor,(void *)auxiliary,1*sizeof(char));
	}
	close(descriptor);
	return 0;
}
/*end eracer code*/
