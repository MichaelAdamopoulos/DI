/* File: mergesort.c */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

Listptr merge(Listptr, Listptr);				// prototype of 'merge' function

Listptr mergesort(Listptr list) {

	Listptr fastptr , slowptr;				// 'slow' and 'fast' pointers to split the list in half

	if ( list == NULL || list->next == NULL )
		return list;
	slowptr = list;
	fastptr = list;
	while ( fastptr->next != NULL ) {			// advancing 'fast' pointer two nodes and 'slow' pointer one node
		fastptr = fastptr->next;			// in order to find the middle of the list
		if ( fastptr->next != NULL ) {
			fastptr = fastptr->next;
			slowptr = slowptr->next;
		}
	}
	fastptr = slowptr;					// spliting the list into two sublists:
	slowptr = slowptr->next;				// 'slow' pointer points to next node
	fastptr->next = NULL;					// previous pointer points to NULL
	return merge(mergesort(list),mergesort(slowptr));	// calling function 'mergesort' to sort the two sublists recursively
}								// and 'merge' to merge those sublists. return sorted list

Listptr merge(Listptr aptr, Listptr bptr) {

        Listptr headptr = NULL;                                 // pointer to new merged list

        if ( aptr == NULL )                                     // base case: if one list ends then the remaining merged list
                return bptr;                                    //            is filled with the other list
        else if ( bptr == NULL )
                return aptr;
        if ( aptr->value > bptr->value ) {			// comparing values
                headptr = bptr;                                 // node with the smallest value is inserted to the merged list
                headptr->next = merge(bptr->next,aptr);         // merging the remaining nodes using recursion
        }
        else {
                headptr = aptr;
                headptr->next = merge(aptr->next,bptr);
        }
        return headptr;                                         // returning the merged list
}
