#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "random.h"
#include "MD5.h"
#include "list.h"

#include "User.h"
#include "mysql.h"

#include "ElgamalSignature.h"
#ifndef __SIGNATUREGAMAL_H__
#define __SIGNATUREGAMAL_H__
#define PATHFILEWITHPRIMESANDGENERATORS "primeNumbersAndGenerators.dat"
#define NAMEFILETEMPORARILY "temporarily"
#define PATHFILEWITHPRIMEANDGENERATORSSELECTED "primeNumberAndGeneratorSelected"
#define LENGHTCOMMAND 70
typedef struct UserPublicKey{
	char nameUser[LENGHTNAME+1];
	PublicKey publicKey;
}UserPublicKey;

void setNumberLinesOfFileWithPrimeNumbersAndGenerators(long );
List getUserPublicKey();
unsigned int powerModule(unsigned int ,unsigned int , unsigned int );
unsigned int euclides(unsigned int ,unsigned int );
int *extendedEuclides(unsigned int , unsigned int );
unsigned int getMultiplicativeInverseUsingExtendedEuclides(unsigned int ,unsigned int );
unsigned int readUnsignedIntOfFile(char *);
long getNumberLinesFile(char *);
unsigned int *getPrimeNumberWithGenerator();
unsigned int getR(unsigned int );
short wasSignature();
short verifySignatureGAMAL(char *);
ElgamalSignature signatureGAMAL(char *);
#endif
