#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef __MD5_H__
#define __MD5_H__
#define STR_VALUE(val) #val
#define STR(name) STR_VALUE(name)
#define PATH_LEN 256
#define MD5_LEN 32
int CalcFileMD5(char *, char *);
#endif
