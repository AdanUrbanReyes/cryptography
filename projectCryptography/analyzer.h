#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//http://es.aliexpress.com/w/wholesale-american-style-hoodies.html
#ifndef __ANALYZER_H__
#define __ANALYZER_H__
typedef union Data{
	int integer;
	double decimal;
	char *string;
}Data;
typedef struct Lexema{
	Data value;
	char *token;
	unsigned int lineNumber;
}Lexema;
char *getLexemaFormatString();
Lexema *recognizedLexema(char *,Data);//receive token, value of token
Lexema *automatonForIntegersNumber();
Lexema *getNextLexema();
short startAnalyzer(char *);//receive file path to analyzer
#endif
