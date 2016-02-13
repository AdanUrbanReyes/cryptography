#include <unistd.h>
#include <inttypes.h>
#include "primeNumbersWithGenerator.h"
void printListUI64(List l){
	while(l.head!=NULL){
		printf("|%"PRIu64"|->",*((uint64_t *)l.head->data));
		l.head=l.head->next;
	}
	printf("NULL\n");
}
Node *indexOf(List l,uint64_t n){
	while(l.head!=NULL){
		if(*((unsigned int *)l.head->data) == n){
			return l.head;
		}
		l.head=l.head->next;
	}
	return NULL;
}
void *replyUI64(uint64_t u){
	uint64_t *r=(uint64_t *)malloc(sizeof(uint64_t));
	if(r==NULL){
		return NULL;
	}
	*r=u;
	return (void *)r;
}
List getListWithUI64(uint64_t s,uint64_t e){
	List l;
	bzero(&l,sizeof(List));
	for(;s<=e;s++){
		if(addNodeToLast(&l,getNode(replyUI64(s),NULL,NULL))==NULL){
			return l;
		}
	}
	return l;
}
List cribaEratostenes(uint64_t s,uint64_t e){
	List p=getListWithUI64(2,e);//list of prime numbers
	if(p.lenght==0){
		return p;
	}
	Node *i=p.head,*t=NULL,*a=NULL;//index,temporarily,auxiliary
	uint64_t d,to=(uint64_t)(sqrt(e));//divisor (ira dividiendo todos los numeros de la ista y si su su residuo es 0 se eliminara),tope
	for(;to>0;to--){
		a=i;//start auxiliary on position i (last number of list where se quedo)
		d=*((uint64_t* )a->data);//set number divisor
		a=a->next;//move one position after pointer a because de lo contrario remove this and this is a error
		while(a!=NULL){//start recorrer list
			if( (*((uint64_t *)a->data)) % d == 0){//question if data on a % d == 0 then remove this node
				t=a->next;//set t one position after because need this for set a other time pointer to list
				removeNode(&p,&a);//remove node of list (a)
				a=t;//set a other time on list
				continue;
			}//if a->data % d != 0 then not remove node avanzo to next position
			a=a->next;//set a next position
		}//when finish of recorrer list pass i to next number of list
		i=i->next;
	}
	for(a=p.head; (*((uint64_t *)a->data)) < s;){
		removeNode(&p,&a);
		a=p.head;
	}
	return p;
}
List getGenerators(uint64_t p){
	List g,r;//g= list of generators,r= list result of pg^n % p
	bzero(&g,sizeof(List));
	bzero(&r,sizeof(List));
	uint64_t pg,t;//pg=probable generador, t=temporarily (save resutl of pg^n % p)
	for(pg=2;pg<p;pg++){
		t=(pg*pg)%p;
		while(indexOf(r,t)==NULL && t!=1 && t!=pg){
			if(addNodeToLast(&r,getNode(replyUI64(t),NULL,NULL))==NULL){
				return g;
			}
			t*=pg;
			t%=p;
		}
		if(r.lenght==p-3){
			if(addNodeToLast(&g,getNode(replyUI64(pg),NULL,NULL))==NULL){
				return g;
			}
		}
		clearList(&r);
	}
	return g;
}
void primeNumbersWithGenerator(uint64_t s,uint64_t e,char *pof){
	List g,p=cribaEratostenes(s,e);//g=generators of each number on list p, p=list of prime numbers
	if(p.lenght==0){
		return;
	}
	bzero(&g,sizeof(List));
	FILE *f=fopen(pof,"a+");
	while(p.head!=NULL){
		fprintf(f,"%"PRIu64":",*((uint64_t*)p.head->data));
		g=getGenerators(*((uint64_t *)p.head->data));
		while(g.head!=NULL){
			fprintf(f,"%"PRIu64,*((uint64_t*)g.head->data));
			if(g.head->next!=NULL){
				fprintf(f,",");
			}
			g.head=g.head->next;
		}
		fprintf(f,"\n");
		clearList(&g);
		p.head=p.head->next;
	}
	fclose(f);
}
