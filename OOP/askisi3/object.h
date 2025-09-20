/* File: object.h */

#include <iostream>
#include <string>

using namespace std;

class String;

class Object {

	protected:
		int id;

	public:
		Object();
		~Object();
		virtual Object *clone() = 0;
		virtual int equal(Object *) = 0;
		int identical(Object *);	// same for all subclasses
		virtual String toString();
		int get_id() const;
};

void clone_encrypt_and_print(Object&);
