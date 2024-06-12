/* File: merge.c */

#include <stdlib.h>

#include "types.h"

Listptr merge(Listptr aptr, Listptr bptr) {

	Listptr headptr = NULL;					// pointer to new merged list

	if ( aptr == NULL )					// base case: if one list ends then the remaining merged list
		return bptr;					// is filled with the other list
	else if ( bptr == NULL )
		return aptr;
	if ( aptr->value > bptr->value ) {			// comparing values
		headptr = bptr;					// node with the smallest value is inserted to the merged list
		headptr->next = merge(bptr->next,aptr);		// merging the remaining nodes using recursion
	}
	else {
		headptr = aptr;
                headptr->next = merge(aptr->next,bptr);
	}
	return headptr;						// returning the merged list
}
