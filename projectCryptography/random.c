#include "random.h"
void setSeed(unsigned int seed){
	srandom(seed);
}
long int getRandomBetween(long int start,long int end){
	if(start>end){
		return getRandom();
	}
	return ((random()%(end-start+1))+start);
}
long int getRandom(){//lower limit upper limit
	return (random() % RAND_MAX);//coregir esto!!! 
}
