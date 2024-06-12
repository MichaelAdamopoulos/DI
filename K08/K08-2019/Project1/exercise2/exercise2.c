/* File: exercise2.c */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "functions.h"

#define ItemFormat "%s"											// ItemFormat is "%s" because ItemType is AirportCode(string)

CompareType compare = &Compare;										// compare points to function 'Compare'

int main(void){

        NodePointer list;

        printf("Creating a new list using 'Create'.\n");
        list = Create();
	if ( list == NULL )
		return -1;
        printf("List: ");
        Print(list, ItemFormat);
        printf("Inserting 'BBB' using 'InsertLast'.\n");
        InsertLast(list, "BBB");
        printf("List: ");
        Print(list, ItemFormat);
        printf("Inserting 'AAA' at the beggining using 'InsertAfter'.\n");
        InsertAfter(list, "AAA", list);									// when 'node = list' we insert item in the beggining
        printf("List: ");
        Print(list, ItemFormat);
        printf("Inserting 'DDD' after 'BBB' using 'InsertAfter'.\n");
        InsertAfter(list, "DDD", Search(list, "BBB", compare));						// we use 'Search' to locate the node with item = 'BBB'
        printf("List: ");
        Print(list, ItemFormat);
	printf("Inserting 'CCC' before 'DDD' using 'InsertBefore'.\n");
	InsertBefore(list,"CCC", Search(list, "DDD", compare));						// we use 'Search' to locate the node with item = 'DDD'
	printf("List: ");
	Print(list, ItemFormat);
        printf("Searching and deleting node with item = 'BBB' using 'Search' and 'Delete'.\n");
        Delete(list, Search(list, "BBB", compare));							// 'Search' returns the node with item = 'BBB'
        printf("List: ");
        Print(list, ItemFormat);
        printf("Deleting last node using 'DeleteLast'.\n");
        DeleteLast(list);
        printf("List: ");
        Print(list, ItemFormat);
}
