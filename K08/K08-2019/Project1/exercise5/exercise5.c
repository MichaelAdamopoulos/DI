/* File: exercise5.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "functions.h"

int main(void) {

	ArrayType Dictionary  = WordArray();					// call function 'WordArray' to create an array with all the dictionary's words
	int i;

	srand((unsigned int) time(NULL));					// seed for random number generator

	for ( i = 0 ; i < 10 ; i++ )						// generate 10 random words from the dictionary
		Similar(Dictionary.Array[rand()%Dictionary.size],Dictionary);	// call function 'Similar' to check for similar words
}										// rand()%Dictionary.size -> [0,size-1]
