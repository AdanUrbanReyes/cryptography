#include "analyzer.h"
FILE *startLexema=NULL,*endLexema=NULL;//startLexema= pointer to the start lexema, endLexema= pointer to the end lexema
unsigned int lineNumber=1;
char characterReaded;//character readed
char *getLexemaFormatString(){
	if(startLexema==NULL || endLexema==NULL){
		return NULL;
	}
	long positionStartLexema=ftell(startLexema);
	long positionEndLexema=ftell(endLexema);
	if((positionEndLexema-positionStartLexema)<1){//is bad becuase startLexema not can't more adelantado that endLexema
		return NULL;
	}
	long indexLexema=0,lenghtLexema=positionEndLexema-positionStartLexema;
	char *lexema=(char *)malloc(sizeof(char)*lenghtLexema+1);//plus one becouse character end of string ('\0')
	while(indexLexema<lenghtLexema){//recover lexema one position antes of el
		lexema[indexLexema++]=(char)fgetc(startLexema);
	}
	lexema[indexLexema]='\0';
	return lexema;
}
Lexema *recognizedLexema(char *token,Data value){
	Lexema *lexema=(Lexema *)malloc(sizeof(Lexema));
	lexema->value=value;
	lexema->token=strdup(token);//use strdup for create a copy of token because this origin (received as parameter) change
	lexema->lineNumber=lineNumber;
	return lexema;
}
Lexema *automatonForId(){
	unsigned int state=0;
	while(1){
		characterReaded=fgetc(endLexema);//read character
		switch(state){
			case 0: 
				if(characterReaded=='\t' || characterReaded==' ' || characterReaded=='\n'){//ignore black space, tabulator, line jump
					fgetc(startLexema);
					if(characterReaded=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(isalpha(characterReaded)!=0){
						state=1;
					}else{
						if(characterReaded=='_'){
							state=2;
						}else{//failure atomaton
							fseek(endLexema,ftell(startLexema),SEEK_SET);//set pointer endLexema(end token) to position pointed by startLexema(start token)      
							return NULL;
						}
					}
				}
			break;
			case 1: 
				if(isalpha(characterReaded)!=0){
					state=3;
				}else{
					if(characterReaded=='_'){
						state=4;
					}else{
						if(isdigit(characterReaded)!=0){
							state=5;
						}else{
							fseek(endLexema,-1,SEEK_CUR);//return one position pointer endLexema because the function getLexemaFormatString required this
							return recognizedLexema("IDENTIFICADOR",(Data)getLexemaFormatString());
						}
					}
				}
			break;
			case 2: 
				if(isalpha(characterReaded)!=0){
					state=3;
				}else{
					if(characterReaded=='_'){
						state=4;
					}else{
						if(isdigit(characterReaded)!=0){
							state=5;
						}else{
							fseek(endLexema,-1,SEEK_CUR);//return one position pointer endLexema because the function getLexemaFormatString required this
							return recognizedLexema("IDENTIFICADOR",(Data)getLexemaFormatString());
						}
					}
				}
			break;
			case 3:
				if(isalpha(characterReaded)!=0){
					state=3;
				}else{
					if(characterReaded=='_'){
						state=4;
					}else{
						if(isdigit(characterReaded)!=0){
							state=5;
						}else{
							fseek(endLexema,-1,SEEK_CUR);//return one position pointer endLexema because the function getLexemaFormatString required this
							return recognizedLexema("IDENTIFICADOR",(Data)getLexemaFormatString());
						}
					}
				}
			break;
			case 4: 
				if(isalpha(characterReaded)!=0){
					state=3;
				}else{
					if(characterReaded=='_'){
						state=4;
					}else{
						if(isdigit(characterReaded)!=0){
							state=5;
						}else{
							fseek(endLexema,-1,SEEK_CUR);//return one position pointer endLexema because the function getLexemaFormatString required this
							return recognizedLexema("IDENTIFICADOR",(Data)getLexemaFormatString());
						}
					}
				}
			break;
			case 5: 
				if(isalpha(characterReaded)!=0){
					state=3;
				}else{
					if(characterReaded=='_'){
						state=4;
					}else{
						if(isdigit(characterReaded)!=0){
							state=5;
						}else{
							fseek(endLexema,-1,SEEK_CUR);//return one position pointer el because the function getLexemaFormatString required this
							return recognizedLexema("IDENTIFICADOR",(Data)getLexemaFormatString());
						}
					}
				}
			break;
		}
	}
}
Lexema *automatonForIntegersNumber(){
	unsigned char state=0;
	while(1){
		characterReaded=fgetc(endLexema);//read character of File
		switch(state){
			case 0: 
				if(characterReaded=='\t' || characterReaded==' ' || characterReaded=='\n'){//remove black space, tabulator, line jump
					fgetc(startLexema);//move startLexema because don't import recover a balck space, tabulator or line jump
					if(characterReaded=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(isdigit(characterReaded)!=0){
						state=1;
					}else{// then this automaton failure for this character
						fseek(endLexema,ftell(startLexema),SEEK_SET);//set pointer el(end token) to position pointed by startLexema(start token)      
						return NULL;
					}
				}
			break;
			case 1://when is state is beause reconozing number 
				if(isdigit(characterReaded)!=0){
					state=1;
				}else{
					fseek(endLexema,-1,SEEK_CUR);//return one position pointer el because the function getLexemaFormatString required this
					return recognizedLexema("INTEGER",(Data)atoi(getLexemaFormatString()));
				}
			break;
		}
	}
}
Lexema *getNextLexema(){
	if(endLexema==NULL || startLexema==NULL){
		return NULL;
	}
	Lexema *lexema;
	unsigned char numberAutomaton=0;
	characterReaded='s';
	while(characterReaded!=EOF){
		switch(numberAutomaton){
			case 0: 
				lexema=automatonForIntegersNumber();
				if(lexema!=NULL){
					return lexema;
				}
			break;//here you can more code for others automatons
			case 1:
				lexema=automatonForId();
				if(lexema!=NULL){
					return lexema;
				}
			break;
			default://here is when any automaton recogniced lexema just return a character not recognized
				fgetc(endLexema);//move pointer endLexema one position for can recuperar a character not recogniced
				return recognizedLexema("ERROR",(Data)getLexemaFormatString());//return character not recogniced
			break;
		}
		numberAutomaton++;
	}
	fclose(endLexema);
	fclose(startLexema);
	endLexema=startLexema=NULL;
	return NULL;
}
short startAnalyzer(char *pathFile){
	if((endLexema=fopen(pathFile,"r"))==NULL){
		return -1;
	}
	startLexema=fopen(pathFile,"r");//is imposibol this line failure because pass if((endLexema=fopen(filePath,"r"))!=NULL)	
	lineNumber=1;
	return 0;
}
