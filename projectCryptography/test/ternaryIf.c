#include <stdio.h>
int testFunction(int i){
	return (i%2==0) ? 1 : 2;
}
int main(int ari,char **arc){
	int i;
	for(i=0;i<7;i++){
		printf("testFunction(%d)=%d\n",i,testFunction(i));
	}
	return 0;
}
1418