#include "signatureGAMAL.h"
User user;
static long numberLinesOfFileWithPrimeNumbersAndGenerators=0;
void *replyUserPublicKey(UserPublicKey userPublicKey){
	UserPublicKey *reply=(UserPublicKey *)malloc(sizeof(UserPublicKey));
	*reply=userPublicKey;
	return (void *)reply;
}
List getUserPublicKey(){		
   strcpy(query,"select u.name, e.primeNumber, e.generator, e.ya from User u, ElgamalSignature e where u.id=e.idUser;");
	List list;
	bzero(&list,sizeof(List));
   UserPublicKey userPublicKey;
   bzero(&userPublicKey,sizeof(userPublicKey));
	if(list.head==NULL)
	if(executeQuery(query)==-1){
      return list;
   }
   /*response=mysql_store_result(connection);
   if(response){
      printf("\t\t\t\tnumberFields = %u\n",mysql_num_fields(response));
              printf("\t\t\t\tfilecount = %u\n",mysql_field_count(connection));
   }
   */
   response=mysql_use_result(connection);
   while ((tupla = mysql_fetch_row(response)) != NULL){
      sscanf(tupla[0],"%[A-Za-z ]",userPublicKey.nameUser);
      sscanf(tupla[1],"%u",&userPublicKey.publicKey.primeNumber);
      sscanf(tupla[2],"%u",&userPublicKey.publicKey.generator);
      sscanf(tupla[3],"%u",&userPublicKey.publicKey.ya);
		addNodeToLast(&list,getNode(replyUserPublicKey(userPublicKey),NULL,NULL));
   }
   return list;
}

void setNumberLinesOfFileWithPrimeNumbersAndGenerators(long numberLines){
	numberLinesOfFileWithPrimeNumbersAndGenerators=numberLines;
}
unsigned int powerModule(unsigned int base,unsigned int exponent, unsigned int module){
	if(module==0 || base==0){
		return 0;
	}
	unsigned int result=1;
	for(;exponent>0;exponent--){ 
		result*=base;
		result%=module;
	}
	return result;
}
unsigned int euclides(unsigned int x,unsigned int y){//this function return greatest common divisor
	unsigned int remainderOld=y,remainderCurrent=x%y;
	if(y>x){
		remainderOld=x;
	}
	while(remainderCurrent!=0){
		remainderOld=remainderCurrent;
		remainderCurrent=y%remainderOld;
		y=remainderOld;
	}
	return remainderOld;//this is a grates common devicer
}
int *extendedEuclides(unsigned int x, unsigned int y){//this function return array that contain multiplicative inverse of x in Z/y and viseversa multiplicative inverse of y in Z/x 
	int quotient=x/y;
	unsigned int remainder=x%y;
	int *last=(int *)malloc(sizeof(int)*4);//here was exprecion of inverse multiplicative (1=ax+by, where a is inverse multiplicative of x in Z/y and b is inverse multiplicative of y in Z/x)
	if(remainder==1){
		last[0]=x;
		last[1]=1;
		last[2]=y;
		last[3]=-1*quotient;
		return last;
	}
	last=extendedEuclides(y,remainder);
	int auxiliary;
	last[0]=x;
	auxiliary=last[1];
	last[1]=last[3];
	last[2]=y;
	last[3]=last[3]*-1*quotient+auxiliary;
	return last;
}
unsigned int getMultiplicativeInverseUsingExtendedEuclides(unsigned int x,unsigned int y){
	int *ee=extendedEuclides(x,y);
	if(ee[1]<0){
		return y-((ee[1]*-1)%y);
	}
	return (ee[1]%y);
}
unsigned int readUnsignedIntOfFile(char *pathFile){
	FILE *file=fopen(pathFile,"r");//this is imposible that faided becuase pass system
	unsigned int unsignedInt=0;
	char *aux=(char *)malloc(sizeof(char)*2);
	fscanf(file,"%u%s",&unsignedInt,aux);
	fclose(file);
	return unsignedInt;
}
long getNumberLinesFile(char *pathFile){
	char command[LENGHTCOMMAND];
	sprintf(command,"wc -l %s | cut -d ' ' -f1 > %s",pathFile,NAMEFILETEMPORARILY);
	system(command);
	return readUnsignedIntOfFile(NAMEFILETEMPORARILY);
}
unsigned int *getPrimeNumberWithGenerator(){
	unsigned int *primeNumberWithGenerator=(unsigned int *)malloc(sizeof(unsigned int)*2);//primeNumberWithGenerator[0]=prime number and primeNumberWithGenerator[1] is generator
	long numberLineRandom=getRandomBetween(1,numberLinesOfFileWithPrimeNumbersAndGenerators);//get a random number line on file that contains prime numbers with generators
	char command[LENGHTCOMMAND];
	sprintf(command,"sed -n %ldp %s > %s",numberLineRandom,PATHFILEWITHPRIMESANDGENERATORS,PATHFILEWITHPRIMEANDGENERATORSSELECTED);//set a line of PATHFILEWITHPRIMESANDGENERATORS on file PATHFILEWITHPRIMEANDGENERATORSSELECTED
	if(system(command)<0){
		return NULL;
	}
	sprintf(command,"sed -i \'s/[,|:]/\\n/g\' %s",PATHFILEWITHPRIMEANDGENERATORSSELECTED);//change characters : and , by \n of file PATHFILEWITHPRIMEANDGENERATORSSELECTED
	if(system(command)<0){
		return NULL;
	}
	primeNumberWithGenerator[0]=readUnsignedIntOfFile(PATHFILEWITHPRIMEANDGENERATORSSELECTED);
	numberLineRandom=getRandomBetween(2,getNumberLinesFile(PATHFILEWITHPRIMEANDGENERATORSSELECTED));
	sprintf(command,"sed -n %ldp %s > %s",numberLineRandom,PATHFILEWITHPRIMEANDGENERATORSSELECTED,NAMEFILETEMPORARILY);//set a line of PATHFILEWITHPRIMEANDGENERATORSSELECTED on file NAMEFILETEMPORARILY
	if(system(command)<0){
		return NULL;
	}
	primeNumberWithGenerator[1]=readUnsignedIntOfFile(NAMEFILETEMPORARILY);
	return primeNumberWithGenerator;
}
unsigned int getR(unsigned int primeNumber){
	unsigned int r=2;
	primeNumber--;
	while(euclides(primeNumber,r)!=1 && (r < primeNumber-1)){
		r++;
	}
	return r;
}
unsigned int MD5ToUnsignedInt(char *pathFile){
	char MD5[MD5_LEN+1];
	unsigned int result=0;
	unsigned char i;
	CalcFileMD5(pathFile,MD5);
	for(i=0;i<=MD5_LEN;i++){
		result+=MD5[i];
	}
	return result;
}
short wasSignature(){
	numberLinesOfFileWithPrimeNumbersAndGenerators=1-numberLinesOfFileWithPrimeNumbersAndGenerators;
	return numberLinesOfFileWithPrimeNumbersAndGenerators;	
}
unsigned int readSignature(char *pathFile){
	unsigned int signature=0;
	FILE *file=fopen(pathFile,"r");
	fseek(file,sizeof(unsigned int) * -1,SEEK_END);//return pointer of file sizeof(unsigned int) from end of file
	fscanf(file,"%u",&signature);
	fclose(file);	
	return signature;
}
short verifySignatureGAMAL(char *pathInFile){
	unsigned int verify,validation,signature;
	ElgamalSignature elgamalSignature;
	bzero(&elgamalSignature,sizeof(ElgamalSignature));
	CalcFileMD5(pathInFile,elgamalSignature.MD5);
	elgamalSignature=getElgamalSignature(elgamalSignature.MD5);
//	if(no regreso nada) regresa ya!
	strcpy(elgamalSignature.idUser,user.id);
	signature=readSignature(pathInFile);
	verify=(powerModule(elgamalSignature.publicKey.ya,elgamalSignature.beta,elgamalSignature.publicKey.primeNumber) * powerModule(elgamalSignature.beta,signature,elgamalSignature.publicKey.primeNumber)) % elgamalSignature.publicKey.primeNumber;	
	validation=powerModule(elgamalSignature.publicKey.generator,elgamalSignature.hash,elgamalSignature.publicKey.primeNumber);
	if(verify!=validation){
		return -1;
	}
	return 0;
}
ElgamalSignature signatureGAMAL(char *pathInFile){
	ElgamalSignature elgamalSignature;
	bzero(&elgamalSignature,sizeof(ElgamalSignature));
	strcpy(elgamalSignature.idUser,user.id);
	unsigned int *primeNumberWithGenerator,r,inverseOfR;	
	primeNumberWithGenerator=getPrimeNumberWithGenerator();
	elgamalSignature.publicKey.primeNumber=primeNumberWithGenerator[0];
	elgamalSignature.publicKey.generator=primeNumberWithGenerator[1];
	elgamalSignature.privateKey=getRandomBetween(2,elgamalSignature.publicKey.primeNumber-2);
	elgamalSignature.publicKey.ya=powerModule(elgamalSignature.publicKey.generator,elgamalSignature.privateKey,elgamalSignature.publicKey.primeNumber);
	r=getR(elgamalSignature.publicKey.primeNumber);
	elgamalSignature.beta=powerModule(elgamalSignature.publicKey.generator,r,elgamalSignature.publicKey.primeNumber);
	inverseOfR=getMultiplicativeInverseUsingExtendedEuclides(r,elgamalSignature.publicKey.primeNumber);
	elgamalSignature.hash=MD5ToUnsignedInt(pathInFile);
	primeNumberWithGenerator[0]=elgamalSignature.hash-(elgamalSignature.publicKey.primeNumber*elgamalSignature.beta);//heare this variable is use as auxiliary for calculate other result
	primeNumberWithGenerator[0]*=inverseOfR;//here this variable is used as auxilirare for other result 
	if(primeNumberWithGenerator[0]<0){
		primeNumberWithGenerator[0]*=-1;
		primeNumberWithGenerator[1]=(elgamalSignature.publicKey.primeNumber-1) - (primeNumberWithGenerator[0] % (elgamalSignature.publicKey.primeNumber-1) );//here this varibale is use as auxiliary for calculate the signature
	}
	primeNumberWithGenerator[1]=primeNumberWithGenerator[0]%(elgamalSignature.publicKey.primeNumber-1);//here this varibale is use as auxiliary for calculate the signature	
	FILE *file=fopen(pathInFile,"a+");
	fprintf(file,"%u",primeNumberWithGenerator[1]);
	fclose(file);	
	CalcFileMD5(pathInFile,elgamalSignature.MD5);
	insertElgamalSignature(elgamalSignature);
	return elgamalSignature;
}
