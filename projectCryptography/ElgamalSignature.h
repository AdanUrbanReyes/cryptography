#include <stdio.h>
#include <string.h>
#include "User.h"
#include "MD5.h"
#include "mysql.h"
#ifndef __ELGAMALSIGNATURE_H__
#define __ELGAMALSIGNATURE_H__
typedef struct PublicKey{
	unsigned int primeNumber;
	unsigned int generator;
	unsigned int ya;
}PublicKey;
typedef struct ElgamalSignature{
	char idUser[LENGHTID+1];//plus one for character end of line
	char MD5[MD5_LEN+1];
	PublicKey publicKey;
	unsigned int privateKey;
	unsigned int beta;
	unsigned int hash;
}ElgamalSignature;
short createTableElgamalSignature();
short insertElgamalSignature(ElgamalSignature );
ElgamalSignature getElgamalSignature(char *);
#endif
