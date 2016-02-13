#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FileCipherWithDES.h"
#include "dataEncryptionStandard.h"
#include "MD5.h"
#include "random.h"
#ifndef __COUNTERMODE_H__
#define __COUNTERMODE_H__
short counterMode(char *,char *,uint64_t ,uint64_t );
short cipher(char *,char *);
short descipher(char *,char *);
#endif
