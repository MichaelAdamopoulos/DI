/* File: main.cpp */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "class.h"

extern int post_id;						// post_id is common for all files

using namespace std;

int main(void) {

	srand(time(NULL));

	date someday;

	someday.day = 12;
	someday.month = 9;
	someday.year = 2000;

	forum OOP("Object-Oriented Programming", someday);
	OOP.print();
	OOP.print_thread("Rules and useful info");

	cout << "Lets print 5 random Posts:" << endl;

	for ( int i = 0 ; i < 5 ; i++ )
		OOP.print_post(rand()%(post_id-1)+1);		// rand()%(post_id-1)+1 returns a random id
								// in the range [1,post_id_max]
	return 0;
}

