#include "dataEncryptionStandard.h"
#include <stdio.h>
unsigned char *initialPermutation=NULL,*initialPermutationInverse=NULL,*permutedChoice1=NULL,*permutedChoice2=NULL,*eBitSelection=NULL,*permutation=NULL,**substitutionBoxs=NULL,*rotations=NULL;

unsigned char **getAddressOfTable(char *n){//n=name table
	return (strcasecmp(n,"eBitSelection")==0) ? &eBitSelection //comare name of table received like parameter and return address memory for this table
	: (strcasecmp(n,"permutation")==0) ? &permutation 
	: (strcasecmp(n,"initialPermutation")==0) ? &initialPermutation
	: (strcasecmp(n,"initialPermutationInverse")==0) ? &initialPermutationInverse
	: (strcasecmp(n,"permutedChoice1")==0) ? &permutedChoice1
	: (strcasecmp(n,"permutedChoice2")==0) ? &permutedChoice2
	: (strcasecmp(n,"substitutionBox1")==0) ? substitutionBoxs
	: (strcasecmp(n,"substitutionBox2")==0) ? substitutionBoxs+1
	: (strcasecmp(n,"substitutionBox3")==0) ? substitutionBoxs+2
	: (strcasecmp(n,"substitutionBox4")==0) ? substitutionBoxs+3
	: (strcasecmp(n,"substitutionBox5")==0) ? substitutionBoxs+4
	: (strcasecmp(n,"substitutionBox6")==0) ? substitutionBoxs+5
	: (strcasecmp(n,"substitutionBox7")==0) ? substitutionBoxs+6
	: (strcasecmp(n,"substitutionBox8")==0) ? substitutionBoxs+7
	: (strcasecmp(n,"rotations")==0) ? &rotations
	: NULL;
}
short loadTables(char *pathFile){
	if(startAnalyzer(pathFile)==-1){//start anayser if some falla return -1
		return -1;
	}
	substitutionBoxs=(unsigned char **)malloc(sizeof(unsigned char *)*NUMBERSUBSTITUTIONBOX);
	unsigned char i;//index selector
	unsigned char **storageSelector;//address memory of table obtenida by function getAddressOfTable
	Lexema *lexema=getNextLexema();//contains data of lexema obtenido by function getNextLexema
	while(lexema != NULL){
		if(strcasecmp(lexema->token,"INTEGER")==0 && storageSelector!=NULL){//if token is a INTEGER and s have a address memory then save the number
			*storageSelector=(unsigned char *)realloc(*storageSelector,sizeof(unsigned char)*(i+1));//get memory for storage data (INTEGER)
			*((*storageSelector)+i)=lexema->value.integer;//save data (INTEGER)
			i++;//increment index of selector for next time that read a INTEGER
		}else{
			if(strcasecmp(lexema->token,"IDENTIFICADOR")==0){//if token is a IDENTIFICADOR restart index selector on 0 and obtiene address memory of table
				i=0;//restart index selector
				storageSelector=getAddressOfTable(lexema->value.string);//get address memory of table (l->v.s contains name of table)	
			}else{
				if(strcasecmp(lexema->token,"ERROR")==0){
					;//here your code for management the errors
				}
			}
		}
		lexema=getNextLexema();
	}
	return 0;
}
unsigned char getBitFromMostSignificant(uint64_t data,unsigned char position){
	if(position>=SIZEOFBLOCKDESONBITS){//if the position supera the size on bits of data then the bit not exist becouse return 0
		return 0;
	}
	uint64_t mask=1;//create a mask that only have one bit turn on
	mask<<=(SIZEOFBLOCKDESONBITS-position-1);//shift bit turn on the number (SIZEOFBLOCKDESONBITS-p-1) because this time start on bit most significat
	return ((data&mask) !=0) ? 1 : 0;//apply mask and if this contains a value distinc of 0 then bit on position p is turn on (return 1) else bit is turn off (return 0)
}
uint64_t * turnOnBitFromMostSignificant(uint64_t *data,unsigned char position){
	if(position>=SIZEOFBLOCKDESONBITS){//if the position supera the size on bits of data then the bit not exist becouse return 0
		return NULL;
	}
	uint64_t mask=1;//create a mask that only have one bit turn on
	mask<<=(SIZEOFBLOCKDESONBITS-position-1);//shift bit turn on the number (SIZEOFBLOCKDESONBITS-p-1) because this time start on bit most significat
	(*data)|=mask;//apply mask with gate OR for only turn on bit on position p sin alter todos los de mas bits
	return data;
}
uint64_t * turnOffBitFromMostSignificant(uint64_t *data,unsigned char position){
	if(position>=SIZEOFBLOCKDESONBITS){//if the position supera the size on bits of data then the bit not exist becouse return 0
		return NULL;
	}
	uint64_t mask=1;//create a mask that only have one bit turn on
	mask<<=(SIZEOFBLOCKDESONBITS-position-1);//shift bit turn on the number (SIZEOFBLOCKDESONBITS-p-1) because this time start on bit most significat
	mask=~mask;//niego mask m because despues will apply gate AND for not alter todos los de mas bits
	(*data)&=mask;//apply mask with gate AND for only turn off bit on position p sin alter todos los de mas
	return data;
}
uint64_t *setBitFromMostSignificant(uint64_t *data,unsigned char position,unsigned char value){
	if(position>=SIZEOFBLOCKDESONBITS || value> 1){//if the position supera the size on bits of data then the bit not exist or if value is disting of 0 or 1 then not is a bit, becouse return 0
		return NULL;
	}
	if(value==1){//then have that turn on bit on position p
		turnOnBitFromMostSignificant(data,position);
	}else{//then have that turn off bit on position p
		turnOffBitFromMostSignificant(data,position);
	}
	return data;
}
uint64_t *getFragments(uint64_t block, unsigned char numberFragments){//b=block, nf= number fragments
	if(numberFragments>SIZEOFBLOCKDESONBITS || numberFragments< 1){//not can more of 64 (becuase b is of 64 bits) fragments or 0 fragments because return NULL
		return NULL;
	}
	uint64_t *fragments=(uint64_t *)malloc(sizeof(uint64_t)*numberFragments);//pido memory for storage fragments
	bzero(fragments,sizeof(uint64_t)*numberFragments);//start memory of fragmets with ceroz
	ssize_t remainingBits=SIZEOFBLOCKDESONBITS;//bits restantes init this with SIZEOFBLOCKDESONBITS because b is the type uint64_t then have a sizeof(uint64_t ) * 8 bits
	unsigned char bitsByFragment,i=0;//i=index of fragments
	uint64_t mask;
	while(block>0){//is block is 0 then not have case that continue because all fragments content ceros and fragment was init with ceros 
		bitsByFragment=remainingBits/numberFragments;//calc how many bits for this fragment
		mask=1;//the next 3 lines counting this, is for create a mask for get the bits of block
		mask<<=bitsByFragment;
		mask-=1;//all this 3 lines is same that pow(mask,bitsByFragment)-1
		fragments[i++]=block&mask;//apply mask and insert bits on fragment and aumento index fragment
		remainingBits-=bitsByFragment;//update bits restant
		numberFragments--;//update numer fragment
		block>>=bitsByFragment;//update block
	}
	return fragments;
}
uint64_t getPermutation(uint64_t block,unsigned char *permutation,unsigned char lenghtPermutation){
	if(lenghtPermutation>SIZEOFBLOCKDESONBITS){// not can't apply permutatition because b is the 64 bits
		return block;
	}
	unsigned char i;//index permutation
	uint64_t result=0;//init with 0 because if l < number bits on b we not want trush on last bits  
	for(i=0;i<lenghtPermutation;i++){//start make permutation
		setBitFromMostSignificant(&result,i,getBitFromMostSignificant(block,permutation[i]-1));//permutation[i]-1 because the position start on 0 in function getBitFromLeastSignificant
	}
	return result;
}
uint32_t *leftShift(uint32_t *block,unsigned char shift){
	shift%=sizeof(uint32_t);//make module becuase if s is mayor that number bits on b asi nos evitamos corrimientos innesesarios ya que al correr el mismo numero de bits en b este queda igual
	if(shift==0){//then dont need make shift
		return block;
	}
	*block=(*block<<shift)^(*block>>(28-shift));//here apply shift the correct is change 28 by sizeof(uint32_t) but for DES not function
	return block;
}
uint64_t getSubkey(uint64_t key,unsigned char round){
	if(round==0 || round>16){//des not have round 0 or more that 16 round then not can calculate subkey
		return key;
	}
	if(round==1){//apply permutation choice 1
		key=getPermutation(key,permutedChoice1,LENGHTPERMUTEDCHOICE1)>>8;//make shift the 8 becuase LENGHTPERMUTEDCHOICE1 only have 56 bits importants
	}
	uint64_t *fragments=getFragments(key,2);
	*(fragments+1)=(*(fragments+1)<<4)^(*fragments>>28);//the next 2 lines are because each block have 28 bits servibles but getFragments not know this
	*fragments&=0xFFFFFFF;
	leftShift((uint32_t *)fragments,rotations[round-1]);//make shift de acuerdo a la round received like parameter
	leftShift((uint32_t *)(fragments+1),rotations[round-1]);//make shift de acuerdo a la round received like parameter
	key=*fragments ^ (*(fragments+1)<<28);//union of Dn and Cn
	key=getPermutation((key<<8),permutedChoice2,LENGHTPERMUTEDCHOICE2)>>16;//make shift the 8 becuase k only have 56 bits important and make shift 16 because LENGHTPERMUTEDCHOICE2 only have 48 bits important
	return key;
}
uint64_t getSubstitutionBoxs(uint64_t block){
	unsigned char i,rowAndColumn,row,column;//i=index for select substitution box
	uint64_t substitution=0;
	for(i=0;i<NUMBERSUBSTITUTIONBOX;i++){
		rowAndColumn=block&0x3F;//get data (6bits) that contains row and column
		row=((rowAndColumn>>4)&2) ^ (rowAndColumn&1);//get row
		column=(rowAndColumn&0x1E)>>1;//get column
		substitution ^= ((uint64_t)substitutionBoxs[7-i][row*16+column]) << (i*4);
		block>>=6;
	}
	return substitution;
}
uint64_t dataEncryptionStandard(uint64_t block,uint64_t key){
	uint64_t *fragments,blockDES;//fragments (Rn=*fragments, Ln=*(fragments+1)), blockDES=this also is used like auxiliary 
	unsigned char i;//index for rounds
	blockDES=getPermutation(block,initialPermutation,LENGHTINITIALPERMUTATION);//apply initial permutation inverse
	fragments=getFragments(blockDES,2);
	for(i=1;i<=NUMBERROUNDS;i++){
		blockDES=*fragments;//used like auxiliary
		*fragments=getPermutation(*fragments<<32,eBitSelection,LENGHTEBITSELECTION)>>16;//apply e-bit selection for expand 32 bits to 48 bits
		key=getSubkey(key,i);//get subkey dependiendo of round
		*fragments=*fragments^key;//XOR between R0 expanded to 48 bits and sub key of round
		*fragments=getSubstitutionBoxs(*fragments);//pass R0 E 48 bits XOR key of round by substitution box
		*fragments=getPermutation(*fragments<<32,permutation,LENGHTPERMUTATION)>>32;//apply permutation p
		*fragments=*fragments ^ *(fragments+1);
		*(fragments+1)=blockDES;
	}
	blockDES= (*(fragments+1)<<32) ^ *fragments;
	blockDES=getPermutation(blockDES,initialPermutationInverse,LENGHTINITIALPERMUTATIONINVERSE);
	return blockDES;
}
