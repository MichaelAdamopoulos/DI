/* File: functions.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

NodePointer Create(void) {

	NodePointer dummy = malloc(sizeof(NodeType));				// creating first "dummy" node

	if ( dummy == NULL ) {
		printf("System memory is exhausted. Couldn't create list.\n");
		return NULL;
	}
	dummy->Link = NULL;
	strcpy(dummy->Airport,"$$$");						// "dummy" does not have an AirportCode as item

	return dummy;
}

void Print(NodePointer list) {

	for ( list = list->Link ; list != NULL ; list = list->Link )		// the initial 'list = list->Link' command skips the dummy node
		printf("%s-->", list->Airport);
	printf("NULL\n");
}

NodePointer Search(NodePointer list, AirportCode item) {

	list = list->Link;							// skip the "dummy" node
	while ( list != NULL )							// access all nodes of the list till we find the given item
		if ( strcmp(list->Airport, item) == 0 )				// compare given and current items
			return list;						// return the node if given item is found
		else
			list = list->Link;
	return list;								// else return NULL
}

void InsertLast(NodePointer list, AirportCode item) {

	NodePointer newnode = malloc(sizeof(NodeType));

	if ( newnode == NULL ) {
		printf("System memory is exhausted. Couldn't insert node.\n");
		return;
	}
	while ( list->Link != NULL )						// access the list till we reach the last node
		 list = list->Link;
	list->Link = newnode;							// create a new node and last node points to new node
	strcpy(newnode->Airport,item);
	newnode->Link = NULL;							// new node points to NULL
}

void InsertAfter(NodePointer list, AirportCode item, NodePointer node) {

	NodePointer newnode = malloc(sizeof(NodeType));				// creating new node

	if ( newnode == NULL ) {
		printf("System memory is exhausted. Couldn't insert node.\n");
		return;
	}
	newnode->Link = node->Link;						// new node points to next node
	strcpy(newnode->Airport,item);
	node->Link = newnode;							// previous node points to new node
}

void DeleteLast(NodePointer list) {

	while ( list->Link->Link != NULL )					// check the 2nd next node till it points to NULL
		list = list->Link;
	free(list->Link);							// free memory
	list->Link = NULL;							// then previous node points to NULL
}

void Delete(NodePointer list, NodePointer node) {

	NodePointer temp;

	while ( list->Link != node )						// access the list till node if found
		list = list->Link;
	temp = list->Link;
	list->Link = list->Link->Link;						// previous node points to next node
	free(temp);								// free memory
}
