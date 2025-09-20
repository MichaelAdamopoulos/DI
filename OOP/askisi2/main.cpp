/* File: main.cpp */

#include <iostream>

#include "class.h"
#include "tree.h"
#include "list.h"

extern int post_id;					// post_id is common for all files

using namespace std;

int main(void) {

	date today;

	today.day = 12;
	today.month = 9;
	today.year = 2000;

	forum OOP("Object-Oriented Programming", today);

	OOP.print_sorted();

	return 0;
}

