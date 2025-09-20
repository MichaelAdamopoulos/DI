/* File: main.cpp */

#include <iostream>
#include <string>

#include "plane.h"

const int plane_capacity = 108;

bool PassengerCompartment::extension = true;		// default value so PassengerCompartment will contain an interior one

using namespace std;

int main(void) {

	cout << "Let's create a Plane!" << endl;

	Plane myplane("myplane", plane_capacity);

	cout << "Let's create some Employees!" << endl;

	CleaningEmployee cleaner("cleaner");
	MaintenanceEmployee maintainer("maintainer");
	SecurityEmployee security("security");

	cout << "Let's have those Employees work on the Plane!" << endl;

	myplane.process(&cleaner);
	myplane.process(&maintainer);
	myplane.process(&security);

	cout << "Let's have those Employees report back on their work!" << endl;

	cleaner.report();
	maintainer.report();
	security.report();

	cout << "Lets check if the Plane is ready to take off!" << endl;

	myplane.ready_check();

	cout << "Calling clone_encrypt_and_print function for the Plane!" << endl;

	clone_encrypt_and_print(myplane);

	return 0;
}
