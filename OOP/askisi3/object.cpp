/* File: object.cpp */

#include <iostream>
#include <string>

#include "string.h"

static int ids = 1;							// each object's id is initialized from this value

Object::Object() {
	this->id = ids;
	ids++;								// after an object is created, raise the ids value for the next object
	cout << "Object just created!" << endl;
}

Object::~Object() {
	cout << "Object to be destroyed!" << endl;
}

int Object::identical(Object *myObject) {
	if ( this == myObject)						// check the memory
		return 1;
	return 0;
}

String Object::toString() {
	return String("Object: ID = " + std::to_string(this->id));
}

int Object::get_id() const {
	return this->id;
}

void clone_encrypt_and_print(Object& myObject) {

	cout << "Cloning the initial object!" << endl;
	Object *newObject = myObject.clone();
	cout << "Comparing the 2 Objects:" << endl;
	if ( newObject->equal(&myObject) == 1 )
		cout << "The 2 Object are equal!" << endl;
	else
		cout << "The 2 Object are not equal!" << endl;
	if ( newObject->identical(&myObject) == 1 )
		cout << "The 2 Object are identical!" << endl;
	else
		cout << "The 2 Object are not identical!" << endl;
	cout << "Converting the 2 Objects to strings!" << endl;
	String myString = myObject.toString();
	String newString = newObject->toString();
	cout << "Updating cloned string!" << endl;
	for ( int i = 0 ; i < 100 ; i++ )				// change characters to 0 at 100 random positions
		newString.updateAt(rand()%newString.lenght(), '0');
	cout << "Printing initial string:" << endl;
	myString.print();
	cout << "Printing cloned string:" << endl;
	newString.print();
	cout << "Concatenating the 2 strings!" << endl;
	myString.concat(newString);
	cout << "Lenght of concatenated string is: " << myString.lenght() << endl;
	if ( myString.lenght()%2 == 0 )
		cout << "Middle characters of string are: " << myString.at(myString.lenght()/2 - 1) << " and " << myString.at(myString.lenght()/2) << endl;
	else
		cout << "Middle character of string is: " << myString.at(myString.lenght()/2) << endl;
	cout << "Clearing concatenated string!" << endl;
	myString.clear();
	cout << "Lenght of emptied string is: " << myString.lenght() << endl;
}
