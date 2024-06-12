/* File: functions.c */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "QueueTypes.h"
#include "QueueFunctions.h"

BTTree BTCreate(void) {

	BTTree Tree;

	if ( ( Tree = malloc(sizeof(struct BTTreeTag) ) ) == NULL )
		return NULL;												// if malloc fails return NULL
	Tree->Height = 0;
	Tree->Size = 0;
	Tree->Root = NULL;
	return Tree;
}

int BTHeight(BTTree Tree) {

	return Tree->Height;
}

int BTSize(BTTree Tree) {

	return Tree->Size;
}

BTNode BTGetRoot(BTTree Tree) {

	return Tree->Root;				// can return NULL if there is no root
}

BTNode BTGetParent(BTTree Tree, BTNode Node) {

	if ( Node == Tree->Root )
		printf("ERROR\n");
	return Node->Parent;
}

BTNode BTGetChildLeft(BTTree Tree, BTNode Node) {

	return Node->LChild;
}

BTNode BTGetChildRight(BTTree Tree, BTNode Node) {

	return Node->RChild;
}

int BTIsNil(BTNode Node) {

	if ( Node->LChild == NULL && Node->RChild == NULL )
		return 1;
	else
		return 0;
}

int BTGetItem(BTTree Tree, BTNode Node) {

	if ( Node == NULL ) {
		printf("ERROR\n");
		return -1;
	}
	else
		return Node->Item;
}

int BTInsertRoot(BTTree Tree, BTItem Item) {

	if ( Tree->Root != NULL ) {
		printf("ERROR\n");
		return 1;
	}
	Tree->Root = malloc(sizeof(struct BTNodeTag));
	Tree->Root->Item = Item;
	Tree->Root->LChild = NULL;
	Tree->Root->RChild = NULL;
	Tree->Root->Parent = NULL;
	Tree->Height = 1;
	Tree->Size = 1;
	return 0;
}

int BTInsertLeft(BTTree Tree, BTNode Node, BTItem Item) {

	if ( Node->LChild != NULL ) {
		printf("ERROR\n");
		return -1;
	}
	Node->LChild = malloc(sizeof(struct BTNodeTag));
	Node->LChild->Item = Item;
	Node->LChild->LChild = NULL;
	Node->LChild->RChild = NULL;
	Node->LChild->Parent = Node;
	return 0;
}

int BTInsertRight(BTTree Tree, BTNode Node, BTItem Item) {

	if ( Node->RChild != NULL ) {
		printf("ERROR\n");
		return -1;
	}
	Node->RChild = malloc(sizeof(struct BTNodeTag));
	Node->RChild->Item = Item;
	Node->RChild->LChild = NULL;
	Node->RChild->RChild = NULL;
	Node->RChild->Parent = Node;
	return 0;
}

int BTRemove(BTTree Tree, BTNode Node) {

	if ( Node->LChild != NULL || Node->RChild != NULL )
		return -1;
	free(Node);
	return 0;
}

void BTChange(BTTree Tree, BTNode Node, BTItem Item) {

	Node->Item = Item;
}

void BTPreOrder(BTTree Tree, BTNode Node, VisitType Visit) {

	if ( Node != NULL ) {
		Visit(Tree, Node);
		BTPreOrder(Tree, Node->LChild, Visit);
		BTPreOrder(Tree, Node->RChild, Visit);
	}
}

void BTInOrder(BTTree Tree, BTNode Node, VisitType Visit) {

	if ( Node != NULL ) {
		BTInOrder(Tree, Node->LChild, Visit);
		Visit(Tree, Node);
		BTInOrder(Tree, Node->RChild, Visit);
	}
}

void BTPostOrder(BTTree Tree, BTNode Node, VisitType Visit) {

	if ( Node != NULL ) {
		BTPostOrder(Tree, Node->LChild, Visit);
		BTPostOrder(Tree, Node->RChild, Visit);
		Visit(Tree, Node);
	}
}

void BTLevelOrder(BTTree Tree, VisitType Visit) {

	Queue Q;
	BTNode Node;

	InitializeQueue(&Q);
	Insert(Tree->Root, &Q);
	while ( !Empty(&Q) ) {
		Remove(&Q, &Node);
		if ( Node != NULL ) {
			Visit(Tree, Node);
			Insert(Node->LChild, &Q);
			Insert(Node->RChild, &Q);
		}
	}
}

void Visit(BTTree Tree, BTNode Node) {

	printf("%d\n", BTGetItem(Tree, Node));
}

