/* File: exercise.c */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "functions.h"

int main(void) {

	NodePointer list;

	printf("Creating a new list using 'Create'.\n");
	list = Create();
	if ( list == NULL )										// if there is no memory to create list, then return
		return -1;
	printf("List: ");
	Print(list);
	printf("Inserting 'BBB' using 'InsertLast'.\n");
	InsertLast(list, "BBB");
	printf("List: ");
	Print(list);
	printf("Inserting 'AAA' at the beggining using 'InsertAfter'.\n");
	InsertAfter(list, "AAA", list);									// when 'node = list' we insert item in the beggining
	printf("List: ");
	Print(list);
	printf("Inserting 'CCC' after 'BBB' using 'InsertAfter'.\n");
	InsertAfter(list, "CCC", Search(list, "BBB"));							// we use 'Search' to locate the node with item = 'BBB'
	printf("List: ");
	Print(list);
	printf("Searching and deleting node with item = 'BBB' using 'Search' and 'Delete'.\n");
	Delete(list, Search(list, "BBB"));								// 'Search' returns the node with item = 'BBB'
	printf("List: ");
	Print(list);
	printf("Deleting last node using 'DeleteLast'.\n");
	DeleteLast(list);
	printf("List: ");
	Print(list);
}
