#include "counterMode.h"
User user;
short counterMode(char *pathInFile,char *pathOutFile,uint64_t initialVector,uint64_t key){
	FILE *inFile=fopen(pathInFile,"rb"),*outFile=fopen(pathOutFile,"wb");
	if(inFile==NULL){
		return -1;
	}
	if(outFile==NULL){
		fclose(inFile);
		return -2;
	}
	size_t bytesReaded;
	uint64_t blockMessage,blockResult;
	while((bytesReaded=fread(&blockMessage,1,SIZEOFBLOCKDES,inFile))>0){
		blockResult=blockMessage ^ dataEncryptionStandard(initialVector++,key);
		fwrite(&blockResult,1,bytesReaded,outFile);
	}
	fclose(inFile);
	fclose(outFile);
	return 0;
}
short cipher(char *pathInFile,char *pathOutFile){
	uint64_t initialVector=(uint64_t)getRandom(),key=(uint64_t)getRandom();//initial vector, key
	if(counterMode(pathInFile,pathOutFile,initialVector,key)<0){
		return -1;
	}
	FileCipherWithDES fileCipherWithDES;
	strcpy(fileCipherWithDES.idUser,user.id);
	CalcFileMD5(pathOutFile,fileCipherWithDES.MD5);
	fileCipherWithDES.initialVector=initialVector;
	fileCipherWithDES.key=key;
	if(insertFileCipherWithDES(fileCipherWithDES)<0){
		return -2;
	}
	return 0;	
}
short descipher(char *pathInFile,char *pathOutFile){
	char MD5[MD5_LEN+1];//plus one for character end of line
	CalcFileMD5(pathInFile,MD5);
	FileCipherWithDES fileCipherWithDES=getFileCipherWithDES(MD5);
	if(!strcmp(fileCipherWithDES.MD5,"00000000000000000000000000000000")){//the query failed !!CORREGIR ESTO
		return -1;
	}
	if(counterMode(pathInFile,pathOutFile,fileCipherWithDES.initialVector,fileCipherWithDES.key)<0){
		return -2;
	}
	return 0;
}
