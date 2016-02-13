#include "shiftCipher.h"
/*
	A-Z 65-90
	a-z 97-122
	A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
	0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
*/
char encryptCharacterWithShiftCipher(char character,int key){
	if(isalpha(character)){//if is a letter of alphabet (A-Z or a-z) then encript
		if(islower(character)){//if is a lower case (a-z)
			character=(((character-ALCA)+key)%LA)+ALCA;
		}else{//then was a upper case (A-Z)
			character=(((character-AUCA)+key)%LA)+AUCA;
		}
	}
	return character;
}
char decryptCharacterWithShiftCipher(char character,int key){
	short auxiliary=0;
	if(isalpha(character)){//if is a letter of alphabet (A-Z or a-z) then encaipt
		if(islower(character)){//if is a lower case (a-z)
			auxiliary=((character-ALCA)-key);
			if(auxiliary<0){
				auxiliary=LA-((auxiliary*-1)%LA);
			}else{
				auxiliary%=LA;
			}
			character=auxiliary+ALCA;
		}else{//then was a upper case (A-Z)
			auxiliary=((character-AUCA)-key);
			if(auxiliary<0){
				auxiliary=LA-((auxiliary*-1)%LA);
			}else{
				auxiliary%=LA;
			}
			character=auxiliary+AUCA;
		}
	}
	return character;
}
short encryptFileWithShiftCipher(char *pathInFile,short key,char *nameOutFile){
	int dif=open(pathInFile,O_RDONLY);//descriptor in file
	int dof=open(nameOutFile,O_WRONLY|O_CREAT,0666);//descriptor out file
	if(dif<0 || dof<0){//culdent open files
		return -1;
	}
	char cr;//character readed or encrypt
	while((read(dif,&cr,SC))>0){
		cr=encryptCharacterWithShiftCipher(cr,key);
		write(dof,&cr,SC);
	}
	close(dif);
	close(dof);
	return 0;
}
short decryptFileWithShiftCipher(char *pathInFile,short key,char *nameOutFile){
	int dif=open(pathInFile,O_RDONLY);//descriptor in file
	int dof=open(nameOutFile,O_WRONLY|O_CREAT,0666);//descriptor out file
	if(dif<0 || dof<0){//culdent open files
		return -1;
	}
	char cr;//character readed or encrypt
	while((read(dif,&cr,SC))>0){
		cr=decryptCharacterWithShiftCipher(cr,key);
		write(dof,&cr,SC);
	}
	close(dif);
	close(dof);
	return 0;
}
char *encryptTextWithShiftCipher(char *plainText,short key){
	size_t lpt=strlen(plainText);//lenght plain text
	unsigned int i;
	char *cipherText=(char *)malloc(lpt);
	char ca;//auxiliary character
	for(i=0;i<lpt;i++){
		ca=plainText[i];
		ca=encryptCharacterWithShiftCipher(ca,key);
		cipherText[i]=ca;
	}
	return cipherText;
}
char *decryptTextWithShiftCipher(char *cipherText,short key){
	size_t lct=strlen(cipherText);//lenght plain text
	unsigned int i;
	char *plainText=(char *)malloc(lct);
	char ca;//auxiliary character
	for(i=0;i<lct;i++){
		ca=cipherText[i];
		ca=decryptCharacterWithShiftCipher(ca,key);
		plainText[i]=ca;
	}
	return plainText;
}
short hackByBruteForce(char *pathInFile,char *nameOutFile){
	int dif=open(pathInFile,O_RDONLY);//descriptor in file
	int dof=open(nameOutFile,O_WRONLY|O_CREAT,0666);//descriptor out file
	if(dif<0 || dof<0){
		return -1;
	}
	short key=1;
	char *limit=(char *)malloc(sizeof(char)*20);// test with key 20\n
	char cr;//character readed or encrypt
	for(key=1;key<26;key++){
		while((read(dif,&cr,SC))>0){
			cr=decryptCharacterWithShiftCipher(cr,key);
			write(dof,&cr,SC);
		}
		sprintf(limit,"\ttest with key %d\n",key);
		write(dof,limit,strlen(limit));
		lseek(dif,0,SEEK_SET);//set pointer to inicio of file
	}
	close(dif);
	close(dof);
	return 0;
}
