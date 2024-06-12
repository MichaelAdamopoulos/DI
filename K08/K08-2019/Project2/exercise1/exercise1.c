/* File: exercise1.c */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "functions.h"

VisitType visit = &Visit;

int main(void) {

	BTNode Root;

	BTTree Tree = BTCreate();

	BTInsertRoot(Tree, 1);
	Root = BTGetRoot(Tree);
	BTInsertLeft(Tree, Root, 2);
	BTInsertRight(Tree, Root, 3);
	BTInsertLeft(Tree, Root->LChild, 4);
	BTInsertRight(Tree, Root->LChild, 5);
	BTInsertLeft(Tree, Root->RChild, 6);
	BTInsertRight(Tree, Root->RChild, 7);
	BTChange(Tree,Root,1);
	BTPreOrder(Tree, Tree->Root, visit);
	printf("\n");
	BTInOrder(Tree, Tree->Root, visit);
	printf("\n");
	BTPostOrder(Tree, Tree->Root, visit);
	printf("\n");
	BTLevelOrder(Tree, visit);
	return 0;
}

