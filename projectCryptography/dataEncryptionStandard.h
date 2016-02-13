#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "analyzer.h"
#ifndef __DATAENCRYPTIONSTANDARD_H__
#define __DATAENCRYPTIONSTANDARD_H__
#define LENGHTINITIALPERMUTATION 64
#define LENGHTINITIALPERMUTATIONINVERSE 64
#define LENGHTPERMUTEDCHOICE1 56
#define LENGHTPERMUTEDCHOICE2 48
#define LENGHTEBITSELECTION 48
#define LENGHTPERMUTATION 32
#define NUMBERSUBSTITUTIONBOX 8
#define LENGHTSUBSTITUTIONBOX 64
#define NUMBERROUNDS 16
#define SIZEOFBLOCKDES 8
#define SIZEOFBLOCKDESONBITS 64
unsigned char **getAddressOfTable(char *);
short loadTables(char *);
unsigned char getBitFromMostSignificant(uint64_t ,unsigned char );
uint64_t * turnOnBitFromMostSignificant(uint64_t *,unsigned char );
uint64_t * turnOffBitFromMostSignificant(uint64_t *,unsigned char );
uint64_t *setBitFromMostSignificant(uint64_t *,unsigned char ,unsigned char );
void printBitsFromMostSignificant(uint64_t ,unsigned char ,unsigned char ,unsigned char );
uint64_t *getFragments(uint64_t , unsigned char );
uint64_t getPermutation(uint64_t ,unsigned char *,unsigned char );
uint32_t *leftShift(uint32_t *,unsigned char );
uint64_t getSubkey(uint64_t ,unsigned char );
uint64_t getSubstitutionBoxs(uint64_t );
uint64_t dataEncryptionStandard(uint64_t ,uint64_t );
#endif
