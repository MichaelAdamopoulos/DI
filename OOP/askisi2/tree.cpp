/* File: tree.cpp */

#include <iostream>
#include <string>
#include <cstdlib>

#include "class.h"
#include "tree.h"
#include "list.h"

using namespace std;

tree::tree() {

	this->root = NULL;
}

void tree::delete_tree(node *nodeptr) {

	if ( nodeptr == NULL )					// use recursion to delete left and right
		return;						// subtree and then the root
	delete_tree(nodeptr->left);
	delete_tree(nodeptr->right);
	delete nodeptr;
	return;
}

tree::~tree() {							// public destructor calls private 'delete_tree'
								// which recursively deletes all nodes of the tree
	delete_tree(this->root);
}

tree::node *tree::create_node(string creator, list *listptr) {

	node *newnode = new node;
	newnode->creator = creator;
	newnode->listptr = listptr;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void tree::insert(string creator, list *listptr, node *nodeptr) {

	if ( root == NULL )					// if tree is empty create first node
		 root = create_node(creator, listptr);
	else if ( nodeptr->creator > creator ) {		// else recursively insert the new node
		if ( nodeptr->left != NULL )			// at the end of the tree
			insert(creator, listptr, nodeptr->left);
		else
			nodeptr->left = create_node(creator, listptr);
		}
	else if ( nodeptr->creator < creator ) {
		if ( nodeptr->right != NULL )
			insert(creator, listptr, nodeptr->right);
		else
			nodeptr->right = create_node(creator, listptr);
		}
	else if ( nodeptr->creator == creator )			// if creator already exists on the tree
		nodeptr->listptr->merge(listptr);		// merge the given list with the existing one

}

void tree::insert(string creator, list *listptr) {		// public 'insert' calls private 'insert'
								// which uses recursion
	insert(creator, listptr, root);
}

void tree::enhance(node *nodeptr) {				// accessing all nodes inorder

	if ( nodeptr != NULL )					// if node exists, insert it to the tree
		this->insert(nodeptr->creator, nodeptr->listptr);
	else
		return;
	if ( nodeptr->left != NULL )				// if there are left and right children,
		this->enhance(nodeptr->left);			// move to those and repeat
	if ( nodeptr->right != NULL )
		this->enhance(nodeptr->right);
}

void tree::enhance(tree *treeptr) {				// public 'enhance' calls private 'enhance'
								// which uses recursion

	if ( this->root == NULL )				// if first tree is empty, then enhanced tree
		this->root = treeptr->root;			// is just the second tree
	else
		this->enhance(treeptr->root);
}

void tree::print_inorder(node *nodeptr) {			// print the tree inorder

	if ( this->root != NULL ) {
		if ( nodeptr->left != NULL )
			this->print_inorder(nodeptr->left);
		nodeptr->listptr->print();			// print the list of posts
		if ( nodeptr->right != NULL )
			this->print_inorder(nodeptr->right);
	}
	else {
		cout << "Tree is empty!" << endl;
	}
}

void tree::print_inorder() {					// public 'print_inorder' calls private 'print_inorder'
								// which uses recursion
	this->print_inorder(this->root);
}

void tree::insert(post *postptr) {

	list *listptr = new list;				// creating a list which contains the given post

	this->insert(postptr->get_creator(), listptr);		// call public 'insert' to insert a node to the tree
}								// with appropriate arguments
