/* File: functions.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

void swapd(char **, char **);

void bubblesort(int n, char **x) {					// sorts an array of 'n' strings using 'bubblesort'

	int i , j;
	char temp[11];							// maximum length of a string is '11'

	for ( i = 1 ; i <= n-1 ; i++ )
		for ( j = n-1 ; j >= i ; j-- )
			if ( strcmp(x[j-1],x[j]) > 0 )
				swapd(&x[j-1],&x[j]);
}

void swapd(char **a, char **b) {					// swaps two strings

	char *temp = *a;
	*a = *b;
	*b = temp;
}

int binsearch(char *w, int n, char **x) {				// searches a string in an array of 'n' strings using 'binary search'

	int cond , low , high , mid;

	low = 0;
	high = n - 1;
	while ( low <= high ) {
		mid = ( low + high ) / 2;
		if ( ( cond = strcmp(w,x[mid]) ) < 0 )
			high = mid - 1;
		else if ( cond > 0 )
			low = mid + 1;
		else
			return 1	;				// word found
	}
	return 0;							// word not found
}

ArrayType WordArray() {							// creates an array filled with the dictionary's words

	FILE *fp = fopen("words","r");					// open stream fp

	int i = 0;
	char a[11];
	ArrayType A;
	A.size = 0;							// initial size of array is 0

	while ( fscanf(fp,"%s",a) != EOF )				// access the dictionary to calculate number of words
		(A.size)++;
	rewind(fp);							// rewind the stream
	A.Array = malloc(A.size*sizeof(char *));			// allocate memory for an array of strings
	for ( i = 0 ; i < A.size ; i++ ) {				// and fill it with the dictionary's words
		A.Array[i] = malloc(11*sizeof(char));
		fscanf(fp,"%s",A.Array[i]);
	}
	bubblesort(A.size,A.Array);					// sort the array
	return A;							// return a struct that includes the array and its size
}

NodePointer Create(void) {						// create a list of strings

	NodePointer dummy = malloc(sizeof(NodeType));
	dummy->Link = NULL;
	strcpy(dummy->word,"\0");

	return dummy;
}

void Print(NodePointer list) {						// print a list of strings

	for ( list = list->Link ; list != NULL ; list = list->Link )

		printf("%s , ", list->word);
	printf("%c%c%c", '\b', '\b', ' ');				// remove last comma
	printf("\n");
}

NodePointer Search(NodePointer list, char *word) {			// search for a string in a list

	list = list->Link;
	while ( list != NULL )
		if ( strcmp(list->word, word) == 0 )
			return list;
		else
			list = list->Link;
	return list;
}

void InsertLast(NodePointer list, WordType word) {			// insert a string at the end of a list

	while ( list->Link != NULL )
		list = list->Link;
	list->Link = malloc(sizeof(NodeType));
	strcpy(list->Link->word, word);
	list->Link->Link = NULL;
}

void Delete(NodePointer list, NodePointer node) {			// delete a string from a list

	while ( list->Link != node )
		list = list->Link;
	list->Link = list->Link->Link;
}
