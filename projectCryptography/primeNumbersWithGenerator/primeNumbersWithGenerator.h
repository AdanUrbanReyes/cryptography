#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "list.h"
#ifndef __PRIMENUMBERSWITHGENERATOR_H__ 
#define __PRIMENUMBERSWITHGENERATOR_H__
void *replyUI(uint64_t );
List getListWithUI(uint64_t , uint64_t);
List cribaEratostenes(uint64_t,uint64_t );
List getGenerators(uint64_t );
void primeNumbersWithGenerator(uint64_t ,uint64_t ,char *);
#endif
