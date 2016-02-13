#include <stdlib.h>
#ifndef __LIST_H__
#define __LIST_H__
typedef struct Node{
	void *data;
	struct Node *next,*previus;
}Node;
typedef struct List{
	size_t lenght;
	Node *head;
}List;
List *clearList(List *);
Node *getNode(void *,Node *,Node *);//return Node with parameters pass first paramenter is the data second is the next pointer and third is previus pointer or NULL in case malloc failded
Node *getNodeByPosition(List ,size_t );//return Node on position pass like parameter (start from 0) or null in case failded
Node *addNodeToLast(List *,Node *);//add node pass like second paramenter to last of list 
//Node *addNodeBeforeOf(List *,Node *);//add node before of elemenent pass like first parameter
//Node *addNodeAfterOf(List **,List *);//add node after of element pass like first paramenter
//Node *removeNode(List *);//remove node pass like first paramenter
Node *removeNode(List *,Node **);//remove node pass like first paramenter
#endif 
