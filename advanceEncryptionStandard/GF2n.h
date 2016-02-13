#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*starteracer me and check make file*/
#include "list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*end eracer me*/
#ifndef __GF2N_H__
#define __GF2N_H__
#define MSOPS 132 //maximum sizeof polynomial string
void exchangeValuesUC(unsigned char *,unsigned char *);//exchange value of first parameter by second parameter
void exchangeValues(unsigned int *,unsigned int *);//exchange value of first parameter by second parameter
unsigned char getDegreePolynomial(unsigned int );//return degree of polynomial received like parameter
unsigned char isTurnedOnBit(unsigned int ,unsigned char );//second parameter is the bit to check is turned on this start from 0, return 1 if is turned on and 0 else
unsigned int convertPolynomialS(char * );//pass polynomial of format string (x^8+x+1) to format binary (100000011) and return binary
char *convertPolynomialUI(unsigned int ,char );//pass polynomial of format unsigned int (01010) to format string (x^3+x^1) and return string
unsigned int modulePolynomial(unsigned int ,unsigned int );//return firs parameter module second parameter
unsigned int multiply(unsigned int ,unsigned int ,unsigned int );//return the multiplication of fist parameter by second parameter module third parameter
unsigned int extendedEuclides(unsigned int ,unsigned int );
char saveListInverses(char *,Node *);
unsigned int *getCopyPolynomialAndHisInverse(unsigned int , unsigned int );
Node *inverseEachElementGF2n(unsigned char ,unsigned int );
#endif
