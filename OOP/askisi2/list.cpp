/* File: list.cpp */

#include <iostream>
#include <string>
#include <cstdlib>

#include "list.h"
#include "class.h"

list::list() {

	this->head = NULL;
}

list::~list() {

	node *current = this->head;
	node *next;

	while ( current != NULL ) {			// delete all nodes of the list
		next = current->next;
		delete current;
		current = next;
	}
	delete this->head;
}

void list::insert(post *postptr) {			// insert new node at the beggining of the list

	node *tmp = new node;				// allocate memory for new post
	tmp->postptr = postptr;
	tmp->next = this->head;
	this->head = tmp;
}

void list::merge(list *listptr) {

	if ( this->head == NULL )			// if first list is empty then merged list
		this->head == listptr->head;		// is just the second list
	else {
		node *current = this->head;

		while ( current->next != NULL ) {	// last node of first list points
			current = current->next;	// to the second list
		}
		current->next = listptr->head;
	}						// NOTE: we can assume that, in the frame of
}							// this exercise and based on the way the lists
							// are created, that there is no pair of lists
							// that contain the same nodes, so we do not
							// need to check

void list::print() {

	if ( this->head == NULL )
		return;

	node *current = this->head;

	while ( current->next != NULL ) {
		current->postptr->print();
		current = current->next;
	}
	current->postptr->print();
}

