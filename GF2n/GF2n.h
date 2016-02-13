#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef __GF2N_H__
#define __GF2N_H__
#define MSOPS 132 //maximum sizeof polynomial string
unsigned char getDegreePolynomial(unsigned int );
void printPolynomial(unsigned int ,char );
unsigned int multiplyBy2RaisedN(unsigned int ,unsigned char );
unsigned char isTurnedOnBit(unsigned int ,unsigned char );
unsigned int extract(unsigned int ,unsigned char ,unsigned char );
unsigned int invert(unsigned int ,unsigned char ,unsigned char );
unsigned int convertStringPolynomialInteger(char *);
unsigned int add(unsigned int ,unsigned int );
unsigned int multiply(unsigned int ,unsigned int ,unsigned int );
#endif
