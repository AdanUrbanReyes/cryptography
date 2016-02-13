#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "list.h"
/*void printListUI(List list){
	while(list.head!=NULL){
		printf("|%u|->",*((unsigned int *)list.head->data));
		list.head=list.head->next;
	}
	printf("NULL\n");
}
void *replyUI(unsigned int ui){
	unsigned int *reply=(unsigned int *)malloc(sizeof(unsigned int));
	*reply=ui;
	return (void *)reply;
}
List getListWithUI(unsigned int start,unsigned int end){
	List listUI;
	bzero(&listUI,sizeof(List));
	for(;start<=end;start++){
		addNodeToLast(&listUI,getNode(replyUI(start),NULL,NULL));
	}
	return listUI;
}
List cribaEratostenes(unsigned int end){
	List primeNumbers=getListWithUI(2,end);
	printListUI(primeNumbers);
	printf("====\n");
	Node *index=primeNumbers.head,*temporarily=NULL,*auxiliary=NULL;
	unsigned int number,top=(unsigned int)sqrt((double)end);
	for(;top>0;top--){	
		auxiliary=index;
		number=*((unsigned int *)auxiliary->data);
		auxiliary=auxiliary->next;
		while(auxiliary!=NULL){
			if((*((unsigned int *)auxiliary->data))%number == 0){
				temporarily=auxiliary->next;
				removeNode(&primeNumbers,&auxiliary);
				auxiliary=temporarily;
				continue;
			}
			auxiliary=auxiliary->next;
		}
		index=index->next;
		printListUI(primeNumbers);
		sleep(1);
	}
	return primeNumbers;
}
unsigned int euclides(unsigned int x,unsigned int y){//this function return greatest common divisor
   unsigned int remainderOld=y,remainderCurrent=x%y;
   if(y>x){
      remainderOld=x;
   }
   while(remainderCurrent!=0){
      remainderOld=remainderCurrent;
//    printf("%u = %u*%u+%u\n",x,y,x/y,remainderCurrent);
      remainderCurrent=y%remainderOld;
      y=remainderOld;
   }
   return remainderOld;//this is a grates common devicer
}
unsigned int getPublicKey(unsigned int fiEuler){
	unsigned int e=2;
	while(euclides(2,fiEuler)!=1){
		e++;
	}
	return e;
}
unsigned int getPrivateKey(unsigned int publicKey,unsigned int fiEuler){
	return extendedEuclides(publicKey,fiEuler);	
}
*/
int main(int ari,char **arc){
		
	return 0;
}
