#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#ifndef __SHIFTCIPHER_H__
#define __SHIFTCIPHER_H__
#define SC sizeof(char) //sizeof char
#define LA 26 //lenght of alphabet
#define ALCA 97 //a lower case ascii
#define AUCA 65//A upper case ascii
char encryptCharacterWithShiftCipher(char character,int key);
char decryptCharacterWithShiftCipher(char character,int key);
short encryptFileWithShiftCipher(char *pathInFile,short key,char *nameOutFile);
short decryptFileWithShiftCipher(char *pathInFile,short key,char *nameOutFile);
char *encryptTextWithShiftCipher(char *plainText,short key);
char *decryptTextWithShiftCipher(char *cipherText,short key);
short hackByBruteForce(char *pathInFile,char *nameOutFile);
#endif //endif __SHIFTCIPHER_H__
