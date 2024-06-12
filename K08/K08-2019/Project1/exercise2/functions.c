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
	dummy->prev = NULL;
	strcpy(dummy->item,"$$$");						// "dummy" does not have an AirportCode as item
	dummy->next = malloc(sizeof(NodeType));					// first "dummy" points to last "dummy" as next node
	dummy->next->next = NULL;						// last "dummy" points to NULL as next node
	dummy->next->prev = dummy;						// and to first "dummy" as previous node
	strcpy(dummy->next->item,"$$$");

	return dummy;
}

void InsertLast(NodePointer list, ItemType item) {

	NodePointer newnode = malloc(sizeof(NodeType));				// creating new node

	if ( newnode == NULL ) {
		printf("System memory is exhausted. Couldn't insert node.\n");
                return;
	}
	while ( list->next->next != NULL )					// checking two nodes ahead to skip the last "dummy"
		list = list->next;
	strcpy(newnode->item,item);
	newnode->next = list->next;						// new node points to last "dummy"
	newnode->prev = list;							// new node points to previously last node
	list->next->prev = newnode;						// last "dummy" points to new node
	list->next = newnode;							// previously last node points to new node
}


void InsertAfter(NodePointer list, ItemType item, NodePointer node) {

	NodePointer newnode = malloc(sizeof(NodeType));				// creating new node

	if ( newnode == NULL ) {
                printf("System memory is exhausted. Couldn't insert node.\n");
                return;
        }
	strcpy(newnode->item,item);
	newnode->next = node->next;						// node points to new node
	newnode->prev = node;							// and new node points to where node used to point
	node->next->prev = newnode;
	node->next = newnode;
}

void InsertBefore(NodePointer list, ItemType item, NodePointer node) {

	NodePointer newnode = malloc(sizeof(NodeType));				// creating new node

	if ( newnode == NULL ) {
                printf("System memory is exhausted. Couldn't insert node.\n");
                return;
        }
	strcpy(newnode->item,item);
	newnode->next =  node;							// new node points to node
	newnode->prev = node->prev;						// and previous node points to new node
	node->prev->next = newnode;
	node->prev = newnode;
}

void DeleteLast(NodePointer list) {

	NodePointer temp;

	while ( list->next->next->next != NULL )				// ckecking three nodes ahead to maintain pre-last node
		list = list->next;
	temp = list->next;
	list->next->next->prev = list;						// last "dummy" points to pre-last node
	list->next = list->next->next;						// pre-last node points to last "dummy"
	free(temp);								// free memory
}

void Delete(NodePointer list, NodePointer node) {

	node->prev->next = node->next;						// previous node points to next node
	node->next->prev = node->prev;						// next node points to previous node
	free(node);								// free memory
}

int Compare(ItemType a, ItemType b) {

	return strcmp(a,b);							// return 0 only if a = b
}

NodePointer Search(NodePointer list, ItemType item, CompareType compare) {

	list = list->next;							// skipping first "dummy"
	while ( list != NULL )
		if ( compare(list->item, item) == 0 )				// if function 'Compare' returns 0 then item is found
			return list;
		else
			list = list->next;					// else check next node
	return list;								// return NULL if item not found
}

void Print(NodePointer list, char *format) {

	printf("NULL<==>");
	for ( list = list->next ; list->next != NULL ; list = list->next ) {	// printing item from all nodes except first and last "dummies"
                printf(format, list->item);
		printf("<==>");
	}
        printf("NULL\n");

}
