/* File: exercise4.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "functions.h"

int main(void) {

	Listptr list = NULL;
	int i;

	srand((unsigned int) time(NULL));			// seed for random number generator

	for ( i = 1 ; i <= 10 ; i++ )				// creating a list with 10 random numbers in [1,100]
		insert_at_end(&list,rand() % 100 + 1);
	printf("Initial list:\n");
	print(list);
	printf("Sorted list:\n");
	print(mergesort(list));					// calling function 'mergesort' to sort the list
}
