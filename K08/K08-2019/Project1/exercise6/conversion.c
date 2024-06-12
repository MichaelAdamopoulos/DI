/* File: conversion.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "functions.h"

void conversion(WordType A, WordType B, ArrayType Dictionary) {			// converts word A to word B

	Queue Q;
	NodePointer list , Slist , Flist , templist;
	int counter = 0;

	InitializeQueue(&Q);							// initialize the queue
	list = Create();
	InsertLast(list,A);
	Insert(list,&Q);							// insert the first list that consists only of word A
	for ( ; ; ) {
		counter++;							// count the loops
		Remove(&Q,&Flist);						// remove a list
		if ( strcmp(Flist->Link->word,B) == 0 ) {			// check if the list's first item is the target
				printf("'%s' converts into '%s'through the following path using %d loops:\n", A, B, counter);
				ReversePrint(Flist);				// if so, print the list and return;
				return;
		}
		Slist = Similar(Flist->Link->word,Dictionary);			// else find all similar words
		if ( Slist == NULL ) {						// if there are none then conversion failed
			printf("Can't convert '%s' into '%s'.\n", A, B);
			return;
		}								// else
		Slist = Slist->Link;						// skip the dummy node
		while ( Slist != NULL ) {					// for every word in the list of similars
			templist = Create();					// create a list
			InsertLast(templist,Slist->word);			// insert the similar word to the list
			templist->Link->Link = Flist->Link;			// insert at the end of the list the remaing conversion path
			Insert(templist,&Q);					// insert the new list to the queue
			Slist = Slist->Link;					// move to next word
			templist = Flist;					// revoke all changes to start over
		}
	}
}
