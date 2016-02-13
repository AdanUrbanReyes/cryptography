#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef __ALGORITHS_H__
#define __ALGORITHS_H__
//start algorith vigenere
#define AACUC 65 //A ASCII CODE UPPER CASE
#define AACLC 97//A ASCII CODE LOWER CASE
#define LA 26//lenght alphabet
/*A-Z=65-90 ascii code*/
/*a-z=97-122 ascii code*/
/*the vigenere in generally is a number that run betwen 0-25*/
char *trim(char *string,char character){
	size_t i,ls=strlen(string);//lenght string
	size_t sc=sizeof(char);//sizeof char
	char *trimmed=(char *)malloc(ls); 
	bzero(trimmed,ls);
	for(i=0;i<ls;i++){
		if(string[i]==character){	
			continue;
		}
		strncat(trimmed,string+i,sc);
	}
	string=(char *)realloc(string,i*sc);
	strcpy(string,trimmed);
	return string;
}
char *isVigenereString(char *string){
	size_t i,ls=strlen(string);//lenght string
	for(i=0;i<ls;i++){
		if(!isalpha(string[i])){
			if(string[i]!=' '){
				return &string[i];
			}
		}
	}
	return NULL;
}
char vigenereToChar(unsigned int vigenere,char flag){//mapeo of number to character,flag said me if is lowercase or uppercase
	if(flag==0){//lowercase
		return 'a'+vigenere;
	}//uppercase
	return 'A'+vigenere;
}
unsigned int charToVigenere(char character){//mapeo of character to number (0-25)
	if(character>=65&&character<=90){
		return character-AACUC;
	}else{
		if(character>=97&&character<=122){
			return character-AACLC;
		}
	}
	return character;
}
unsigned int *stringToVigenere(char *string){//mapeo of characteres to numbers (0-25)
	size_t i,ls=strlen(string);//lenght string
	unsigned int *vigenere=(unsigned int *)malloc(sizeof(unsigned int)*ls);
	for(i=0;i<ls;i++){
		if(isalpha(string[i])){//if is a character of alphabet (A, B, C, ... ,Z or a, b, c, ... , z)
			vigenere[i]=charToVigenere(string[i]);
		}
	}
	vigenere=(unsigned int *)realloc(vigenere,sizeof(unsigned int)*i);
	return vigenere;
}
char *encryptWithVigenere(char *plainText,char *key){
//	unsigned int *plainTextVigenere=stringToVigenere(plainText);//mapeo de nu
//	unsigned int *keyVigenere=stringToVigenere(key);
//	unsigned int i,j,k;//i for shift plainText and j for shift keyVigenere
	/*size_t lpt=strlen(plainText);//lenght plain text
	size_t lkv=sizeof(keyVigenere);//lenght keyVigenere
	char *cipherText=(char *)malloc(lpt);
	for(i=0,j=0,k=0;i<lpt;i++){
		if(!isalpha(plainText[i])){//if not is the alphabet (if not is abc..z or ABC..Z), then not encrypt
			cipherText[i]=plainText[i];
			continue;
		}//if is a character of alphabet encrypt
		cipherText[i]=plainTextVigenere[k++]+keyVigenere[j++]%LA;
		if(j>=(lkv-1)){
			j=0;
		}
	}
	return cipherText;
	*/
	return NULL;
}
char *descryptWithVigenere(char *cipherText,char *key){
	/*size_t lk=strlen(key);//lenght key		
	size_t lct=strlen(cipherText);//lenght plain text
	char *plainText=(char *)malloc(lct);
	printf("lct=%zu",lct);
	size_t i,j;
	int auxiliary;
	size_t *keyVigenere=stringToVigenere(key);//is that auxiliary for not call all time to function charToVigenere
	for(i=0,j=0;i<lct;i++){
		if(!isalpha(cipherText[i])){//if not is the alphabet (if not is abc..z or ABC..Z), then not encrypt
			plainText[i]=cipherText[i];
			continue;
		}//if is a character of alphabet encrypt
		auxiliary=charToVigenere(cipherText[i])-keyVigenere[j];
		if(auxiliary<0){
			auxiliary=LA+auxiliary;	
		}
		plainText[i]=vigenereToChar(auxiliary);
		if((j++)>=(lk-1)){
			j=0;
		}
	}
	return plainText;
	*/
	return NULL;
}
//end algorith vigenere
#endif
