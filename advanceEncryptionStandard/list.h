#include <stdlib.h>
#ifndef __LIST_H__
#define __LIST_H__
typedef struct node{
	void *data;
	struct node *next,*previus;
}Node;
Node *getNode(void *,Node *,Node *);//return Node with parameters pass first paramenter is the data second is the next pointer and third is previus pointer
Node *getNodeByPosition(Node *,unsigned int );
Node *addNode(Node **,Node *);//add node to list first paramenter is pointer to start list and second is node to add, return node added
Node *addNodeBeforeOf(Node **,Node *);//add node before of elemenent pass like first parameter
Node *addNodeAfterOf(Node **,Node *);//add node after of element pass like first paramenter
Node *removeNode(Node **);//remove node pass like first paramenter
#endif 
