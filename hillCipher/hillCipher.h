#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "unidimensionalMatrix.h"
#ifndef __HILLCIPHER_H__
#define __HILLCIPHER_H__
#define LAC 127 //lenght of asiic code
#define LA 26 //lenght of alphabet
#define ALCA 97 //a lower case ascii
#define AUCA 65//A upper case ascii
unsigned int *applyModuleToArray(int *,unsigned int ,unsigned int );
char *arrayIntegersToArrayAlphabet(int *,unsigned int );
short encryptFileWithHillCipher(char *,int *,unsigned int ,unsigned int ,char *);
short descryptFileWithHillCipher(char *,int *,unsigned int ,unsigned int ,char *);
#endif
