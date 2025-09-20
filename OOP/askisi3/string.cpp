/* File: string.cpp */

#include <iostream>
#include <string>

#include "string.h"

using namespace std;

String::String(string mystr) {
	cout << "String just created!" << endl;
	this->mystr = mystr;
}

String::~String() {
	cout << "String to be destroyed!" << endl;
}

int String::lenght() const {
	return this->mystr.length();
}

void String::clear() {
	this->mystr.clear();
}

void String::concat(String &str) {
	this->mystr = this->mystr + str.mystr;
}

const char& String::at(int pos) const {			// make sure character at position pos exists
	if ( 0 < pos < this->lenght() )
		return this->mystr.at(pos);
}

void String::updateAt(int pos, char newchar) {		// make sure character at position pos exists
	if ( 0 < pos < this->lenght() )
		this->mystr[pos] = newchar;
}

void String::print() const {
	cout << this->mystr << endl;
}

string String::get_string() const {
	return this->mystr;
}

String *String::clone() {
	String *newstr = new String(this->mystr);
	newstr->id = this->id;
	return newstr;
}

int String::equal(Object *str) {			// casting Object * to String * to access data-members of class String
	if ( dynamic_cast<String *>(str) == NULL )
		return 0;				// if cast fails return 0(not equal)
	if ( this->id == dynamic_cast<String *>(str)->id )
		if ( this->mystr == dynamic_cast<String *>(str)->mystr )
			return 1;
	return 0;
}

String String::toString() {				// String's toString returns Object's toString plus the rest data-members
	return String("String: " + Object::toString().get_string() + ", mystr = " + this->mystr);
}
