////////////////////////////////
//
// Υλοποίηση του pq_sort module
//
////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#include "pq_sort.h"
#include "ADTPriorityQueue.h"

void pq_sort_vector(Vector vec, CompareFunc compare) {
	// Προσοχή! Μέσα στη συνάρτηση αυτή θα χρειαστεί να αντικαταστήσουμε τα περιεχόμενα του vector. Δε
	// θέλουμε όμως όσο το κάνουμε αυτό το vector να καλέσει τη destroy! Οπότε αλλάζουμε προσωρινά τη
	// συνάρτηση destroy σε NULL (αποθηκεύοντας την παλιά τιμή).
	DestroyFunc old_destroy = vector_set_destroy_value(vec, NULL);

	// κυρίως λειτουργία της συνάρτησης
	PriorityQueue pq = pqueue_create(compare, NULL, vec);
	for (int pos = vector_size(vec)-1; pos >= 0; pos--) {
		Pointer max = pqueue_max(pq);
		vector_set_at(vec, pos, max);
		pqueue_remove_max(pq);
		}	

	// επαναφορά της destroy
	vector_set_destroy_value(vec, old_destroy);
}

void pq_sort_list(List list, CompareFunc compare) {

	PriorityQueue pq = pqueue_create(compare, NULL, NULL);

	// Same as with vector
	DestroyFunc old_destroy = list_set_destroy_value(list, NULL);
	
	int counter = list_size(list);

	// remove all nodes from the list and insert them to the queue
	for (int i = 0; i < counter; i++) {
		int *value = malloc(sizeof(int));
		value = (int *)list_node_value(list, list_first(list));
		pqueue_insert(pq, value);
		list_remove_next(list, LIST_BOF);		
	}

	// insert all the nodes from the queue to the list in correct order
	for (int i = 0; i < counter; i++) {
		int *value = malloc(sizeof(int));
		value = (int *)pqueue_max(pq);
		list_insert_next(list, LIST_BOF, value);
		pqueue_remove_max(pq);
	}

	list_set_destroy_value(list, old_destroy);
}