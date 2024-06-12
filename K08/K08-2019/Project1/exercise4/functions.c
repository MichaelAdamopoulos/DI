/* File: functions.c */

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

void insert_at_end(Listptr *ptraddr, int v) {           // inserts a new node at the end of a list

        while ( *ptraddr != NULL )
                ptraddr = &((*ptraddr)->next);
        *ptraddr = malloc(sizeof(struct listnode));
        (*ptraddr)->value = v;
        (*ptraddr)->next = NULL;
}

void print(Listptr list) {                              // prints all nodes of a list
        while ( list != NULL ) {
                printf("%d-->", list->value);
                list = list->next;
        }
        printf("NULL\n");
}
