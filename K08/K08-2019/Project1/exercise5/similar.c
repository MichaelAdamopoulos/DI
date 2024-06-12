/* File: similar.c */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "functions.h"

void Similar(char *word, ArrayType A) {

	NodePointer list = Create();							// create the list with the similar words
	char temp[strlen(word)+1];							// temporary string with length same as 'word'
	int i = 0;

	strcpy(temp,word);								// copy word to temp
	while ( temp[i] != '\0' ) {							// access all characters of 'temp' till we reach the end
                for ( temp[i] = 'a' ; temp[i] <= 'z' ; temp[i]++ )			// change a character with every letter of the alpabet
                                        if ( binsearch(temp,A.size,A.Array) == 1 )	// then check if the new word exists in the dictionary
                                                        InsertLast(list,temp);		// if it does, insert it to the list
                strcpy(temp,word);							// reset all changes
                i++;									// move to next character
        }
	for ( i = 0 ; i < strlen(word) ; i++ )
               Delete(list, Search(list, word));					// exclude from the list the prototype words

	if ( list->Link == NULL )
		printf("There are no similar words to '%s'.\n", word);
	else {
		printf("The following words are similar to '%s': ", word);
		Print(list);
	}
}
