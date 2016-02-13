#include "list.h"
List *clearList(List *list){
	Node *auxiliary=NULL;
	while(list->head!=NULL){
		auxiliary=list->head;
		list->head=auxiliary->next;
		free(auxiliary);
	}
	list->head=NULL;
	list->lenght=0;
	return list;
}
Node *getNode(void *data, Node *next, Node *previus){
	Node *node=(Node *)malloc(sizeof(Node));
	if(node==NULL){
		return node;
	}
	node->data=data;
	node->next=next;
	node->previus=previus;
	return node;
}
Node *getNodeByPosition(List list,size_t position){
	while(position>0 && list.head!=NULL){
		list.head=list.head->next;
		position--;
	}
	return list.head;
}
Node *addNodeToLast(List *list,Node *toAdd){
	if(toAdd==NULL){
		return NULL;
	}
	if(list->head==NULL){
		list->head=toAdd;
		list->lenght=1;
	}else{
		Node *auxiliary=list->head;
		while(auxiliary->next!=NULL){
			auxiliary=auxiliary->next;
		}
		auxiliary->next=toAdd;
		toAdd->previus=auxiliary;
		list->lenght++;
	}
	return toAdd;
}
Node *addNodeBeforeOf(Node **of,Node *toAdd){
	if(*of==NULL || toAdd==NULL){
		return NULL;
	}
	toAdd->next=(*of);//set like next element of toAdd the element *of
	toAdd->previus=(*of)->previus;//set like previus of toAdd the previus element of *of
	if((*of)->previus!=NULL){
		((*of)->previus)->next=toAdd;//set pointer next of previus element of *of for toAdd
	}else{//then (*of) is head of list then need move pointer head to start list (toAdd)
		(*of)->previus=toAdd;//set pointer previus of *of for toAdd
		*of=toAdd;// move *of for toAdd (move header of list to new header list)
		return toAdd;//return element added
	}
	(*of)->previus=toAdd;//set pointer previus of *of for toAdd
	return toAdd;//return element added
}
Node *addNodeAfterOf(Node **of,Node *toAdd){
	if(*of==NULL || toAdd==NULL){
		return NULL;
	}
	toAdd->previus=(*of);
	toAdd->next=(*of)->next;
	if((*of)->next!=NULL){
		((*of)->next)->previus=toAdd;
	}
	(*of)->next=toAdd;
	return toAdd;
}
Node *removeNode(List *list,Node **toRemove){
	if(*toRemove==NULL){
		return NULL;
	}
	Node *auxiliary=*toRemove;
	if((*toRemove)->previus==NULL){//then (*toRemove) is head of list then need move pointer head to start list (*toRemove)->next;
		*toRemove=(*toRemove)->next;//move toRemove (header of list) to next elemente 
		list->head=*toRemove;
		if(list->head!=NULL){
			(*toRemove)->previus=NULL;//set pointer previus with null (head->previus=NULL)
		}
	}else{
		if(auxiliary->next!=NULL){//if next not is null
			(auxiliary->next)->previus=auxiliary->previus;//set previus of next element of auxiliary with previus element of auxiliary
		}
		if(auxiliary->previus!=NULL){//if previus not is null
			(auxiliary->previus)->next=auxiliary->next;//set next of previus element of auxiliary with next element of auxiliary
		}
	}
	auxiliary->next=auxiliary->previus=NULL;//set null pointer of auxiliary (here is where remove element :D)
	list->lenght--;
	return auxiliary;//return element droped
}
