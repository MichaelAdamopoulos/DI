/* File: functions.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "functions.h"

// QUEUE's FUNCTIONS

void InitializeQueue(Queue *Q) {

	Q->Front = NULL;
	Q->Rear = NULL;
}

void Insert(NodePointer list, Queue *Q) {

	QueueNode *Temp = (QueueNode *)malloc(sizeof(QueueNode));

	if ( Temp == NULL )
		printf("System storage is exhausted\n");
	else {
		Temp->list = list;
		Temp->Link = NULL;
		if ( Q->Rear == NULL ) {
			Q->Front = Temp;
			Q->Rear = Temp;
		}
		else {
			Q->Rear->Link = Temp;
			Q->Rear = Temp;
		}
	}
}

void Remove(Queue *Q, NodePointer *F) {

	QueueNode *Temp;

	if ( Q->Front == NULL )
		printf("Attempt to remove item from an empty queue\n");
	else {
		*F = Q->Front->list;
		Temp = Q->Front;
		Q->Front = Temp->Link;
		free(Temp);
 		if ( Q->Front == NULL )
			 Q->Rear = NULL;
	}
}

// LIST's FUNCTIONS

NodePointer Search(NodePointer list, char *word) {

	list = list->Link;
	while ( list != NULL )
		if ( strcmp(list->word, word) == 0 )
			return list;
		else
			list = list->Link;
	return list;
}

void Delete(NodePointer list, NodePointer node) {

	while ( list->Link != node )
		list = list->Link;
	list->Link = list->Link->Link;
}


NodePointer Create(void) {

	NodePointer dummy = malloc(sizeof(NodeType));
	dummy->Link = NULL;
	strcpy(dummy->word,"\0");

	return dummy;
}

void InsertLast(NodePointer list, char *word) {

	while ( list->Link != NULL )
		list = list->Link;
	list->Link = malloc(sizeof(NodeType));
	strcpy(list->Link->word, word);
	list->Link->Link = NULL;
}

void InsertAfter(NodePointer list, WordType word, NodePointer node) {

	NodePointer newnode = malloc(sizeof(NodeType));

	newnode->Link = node->Link;
	strcpy(newnode->word,word);
	node->Link = newnode;
}

NodePointer Similar(char *word, ArrayType A) {					// 'Similar' returns a list with all the similar words

	NodePointer list = Create();
	char temp[strlen(word)+1];
	int i = 0;

	strcpy(temp,word);
	while ( temp[i] != '\0' ) {
		for ( temp[i] = 'a' ; temp[i] <= 'z' ; temp[i]++ )
			if ( binsearch(temp,A.size,A.Array) == 1 )
				InsertLast(list,temp);
			strcpy(temp,word);
		i++;
	}
	for ( i = 0 ; i < strlen(word) ; i++ )
		Delete(list, Search(list, word));
	if ( list->Link == NULL )
		return NULL;
	else
		return list;
}

void Print(NodePointer list) {

        for ( list = list->Link ; list != NULL ; list = list->Link )
                printf("%s-->", list->word);
        printf("%c%c%c%c%c%c", '\b', '\b', '\b', ' ', ' ', ' ');
        printf("\n");
}

void ReversePrint(NodePointer list) {						// reverse print the nodes of a list

	NodePointer reverse = Create();						// create a new reverse list

	for ( list = list->Link ; list != NULL ; list = list->Link )		// access all nodes of the list
		InsertAfter(reverse,list->word,reverse);			// and insert them at the beggining of the reverse list
	Print(reverse);								// then print the reverse list
}

// ARRAY's FUNCTIONS

ArrayType WordArray() {

	FILE *fp = fopen("words","r");

	int i = 0;
	char a[11];
	ArrayType A;
	A.size = 0;

	while ( fscanf(fp,"%s",a) != EOF )
		(A.size)++;
	rewind(fp);
	A.Array = malloc(A.size*sizeof(char *));
	for ( i = 0 ; i < A.size ; i++ ) {
		A.Array[i] = malloc(11*sizeof(char));
		fscanf(fp,"%s",A.Array[i]);
	}
	bubblesort(A.size,A.Array);
	return A;
}

void swapd(char **a, char **b) {

	char *temp = *a;
	*a = *b;
	*b = temp;
}

void bubblesort(int n, char **x) {

	int i , j;
	char temp[11];

	for ( i = 1 ; i <= n-1 ; i++ )
		for ( j = n-1 ; j >= i ; j-- )
			if ( strcmp(x[j-1],x[j]) > 0 )
				swapd(&x[j-1],&x[j]);
}

int binsearch(char *w, int n, char **x) {

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
			return 1;
		}
	return 0;
}
