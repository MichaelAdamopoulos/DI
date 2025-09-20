///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT BList μέσω διπλά συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTBList.h"


// Ενα BList είναι pointer σε αυτό το struct
struct blist {
	BListNode first;	// dummy node at the beginning
	BListNode last;		// dummy node at the end
	int size;
	DestroyFunc destroy_value;
};

struct blist_node {
	BListNode next;
	BListNode prev;
	Pointer value;
};


BList blist_create(DestroyFunc destroy_value) {

	BList blist = malloc(sizeof(*blist));
	blist->size = 0;
	blist->destroy_value = destroy_value;

	// dummy nodes point to one another
	blist->first = malloc(sizeof(*blist->first));
	blist->last = malloc(sizeof(*blist->last));
	blist->first->next = blist->last;
	blist->first->prev = NULL;
	blist->last->prev = blist->first;
	blist->last->next = NULL;

	return blist;
}

int blist_size(BList blist) {
	return blist->size;
}

void blist_insert(BList blist, BListNode node, Pointer value) {

	BListNode new = malloc(sizeof(*new));
	new->value = value;

	if (node == NULL)
		node = blist->last;

	new->next = node;
	new->prev = node->prev;
	new->prev->next = new;
	new->next->prev = new;

	blist->size++;
}

void blist_remove(BList blist, BListNode node) {

	if (blist->destroy_value != NULL)
		blist->destroy_value(node->value);

	node->next->prev = node->prev;
	node->prev->next = node->next;

	free(node);

	blist->size--;
}

Pointer blist_find(BList blist, Pointer value, CompareFunc compare) {
	BListNode node = blist_find_node(blist, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc blist_set_destroy_value(BList blist, DestroyFunc destroy_value) {
	DestroyFunc old = blist->destroy_value;
	blist->destroy_value = destroy_value;
	return old;
}

void blist_destroy(BList blist) {
	
	BListNode node = blist->first;

	while (node != blist->last) {
		node = node->next;
		if (node != blist->first &&	blist->destroy_value != NULL)
			blist->destroy_value(node->value);
		free(node->prev);	
	}
	free(blist->last);
	free(blist);
}


// Διάσχιση της λίστας /////////////////////////////////////////////

BListNode blist_first(BList blist) {
	if (blist->first->next == blist->last)
		return BLIST_BOF;
	else
		return blist->first->next;	
}

BListNode blist_last(BList blist) {
	if (blist->last->prev == blist->first)
		return BLIST_EOF;
	else
		return blist->last->prev;
}

BListNode blist_next(BList blist, BListNode node) {
	if (node->next == NULL)
		return BLIST_EOF;
	else
		return node->next;
}

BListNode blist_previous(BList blist, BListNode node) {
	if (node->prev == NULL)
		return BLIST_BOF;
	else
		return node->prev;
}

Pointer blist_node_value(BList blist, BListNode node) {
	return node->value;
}

BListNode blist_find_node(BList blist, Pointer value, CompareFunc compare) {
	// διάσχιση όλης της λίστας, καλούμε την compare μέχρι να επιστρέψει 0
	//
	for (BListNode node = blist->first->next; node != blist->last; node = node->next)
		if (compare(value, node->value) == 0)
			return node;		// βρέθηκε

	return NULL;	// δεν υπάρχει
}