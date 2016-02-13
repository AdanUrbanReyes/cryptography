#include "unidimensionalMatrix.h"
#include "GF2n.h"
/*starteracer me */
#include "list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
/*end eracer me*/
#ifndef __ADVANTACEENCRYPTIONSTANDARD_H__
#define __ADVANTACEENCRYPTIONSTANDARD_H__
#define STM 31 //step three multiplication (x^4+x^3+x^2+x^1+1)
#define MSTM 257 //mudule of step three multiplication (x^8+1)
#define SFA 99 //step four add (x^6+x^5+x^1+1)
#define IP 283 //irreducible polynomial (x^8+x^4+x^3+x^1+1)
unsigned char *getSubstitutionBox();
unsigned char *shiftUp(unsigned char *);
unsigned char *exchangeBySubstitutionBox(unsigned char *,unsigned char *);
unsigned char getCi(unsigned char ,unsigned int );
Node *keyExpansion(unsigned char *,unsigned char );
char saveTableSubstitutionBox(char *,unsigned char *,unsigned int ,unsigned char );
#endif
