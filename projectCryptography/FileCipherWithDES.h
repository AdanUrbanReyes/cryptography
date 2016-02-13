#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "User.h"
#include "mysql.h"
#include "MD5.h"
#ifndef __FILECIPHERWITHDES_H__
#define __FILECIPHERWITHDES_H__
typedef struct FileCipherWithDES{
	char idUser[LENGHTID+1];//plus one by character end of line 
	char MD5[MD5_LEN+1];
	uint64_t initialVector;
	uint64_t key;
}FileCipherWithDES;
short createTableFileCipherWithDES();
short insertFileCipherWithDES(FileCipherWithDES );
FileCipherWithDES getFileCipherWithDES(char *);
#endif
