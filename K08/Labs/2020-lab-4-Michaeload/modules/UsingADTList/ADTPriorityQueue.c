///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω ταξινομημένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTList.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί List


// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct priority_queue {
	List list;		// η λίστα στην οποία αποθηκεύουμε τα στοιχεία
	CompareFunc compare;
	DestroyFunc destroy_value;
};

// Συναρτήσεις του ADTPriorityQueue //////////////////////////////////////////////////

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	
	PriorityQueue pqueue = malloc(sizeof(*pqueue));
	pqueue->compare = compare;
	pqueue->destroy_value = destroy_value;

	pqueue->list = list_create(destroy_value);
	
	if (values == NULL)
		return pqueue;
	
	for (int i = 0; i != vector_size(values); i++)
		pqueue_insert(pqueue, vector_get_at(values, i));

	// Για την κλήση της συνάρτησης destroy_value, την περνάμε απλά στη list_create
	// οπότε θα καλείται αυτόματα όταν το στοιχείο αφαιρεθεί από τη λίστα.
	// ... = list_create(destroy_value);

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue) {
	return list_size(pqueue->list);
}

Pointer pqueue_max(PriorityQueue pqueue) {
	return list_node_value(pqueue->list, list_first(pqueue->list));
}

void pqueue_insert(PriorityQueue pqueue, Pointer value) {

	ListNode temp = list_first(pqueue->list);
	if (temp == LIST_BOF)
		list_insert_next(pqueue->list, LIST_BOF, value);
	else if (pqueue->compare(value, list_node_value(pqueue->list, temp)) > 0)
		list_insert_next(pqueue->list, LIST_BOF, value);
	else {
		temp = list_next(pqueue->list, temp);
		ListNode prev = list_first(pqueue->list);
		while (temp != LIST_EOF && pqueue->compare(value, list_node_value(pqueue->list, temp)) <= 0) {
			temp = list_next(pqueue->list, temp);
			prev = list_next(pqueue->list, prev);
		}
		list_insert_next(pqueue->list, prev, value);
	}
}

void pqueue_remove_max(PriorityQueue pqueue) {
	list_remove_next(pqueue->list, LIST_BOF);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	// Απλά καλούμε την αντίστοιχη συνάρτηση της λίστας
	return list_set_destroy_value(pqueue->list, destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue) {
	list_destroy(pqueue->list);
	free(pqueue);
}
