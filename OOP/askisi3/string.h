/* File: string.h */

#include <iostream>
#include <string>

#include "object.h"

using namespace std;

class String : public Object {

	private:
		string mystr;

	public:
		String(string);
		~String();
		int lenght() const;
		void clear();
		void concat(String&);
		const char& at(int) const;
		void updateAt(int , char);
		void print() const;
		string get_string() const;
		String *clone();
		int equal(Object *);
		String toString();
};
