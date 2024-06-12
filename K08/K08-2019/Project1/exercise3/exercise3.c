/* File: exercise2.c */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "functions.h"

int main(void) {

	Listptr aptr = NULL , bptr = NULL;	// pointers for two lists
	int i;

	for ( i = 1 ; i < 25 ; i += 2 )		// creating and inserting nodes to make two sorted lists
		insert_at_end(&aptr,i);
	for ( i = 1 ; i < 30 ; i += 3 )
		insert_at_end(&bptr,i);
	printf("First list:\n");		// printing initial lists
	print(aptr);
	printf("Second list:\n");
	print(bptr);
	printf("Merged list:\n");
	print(merge(aptr,bptr));		// merging and printing the new sorted list
}
