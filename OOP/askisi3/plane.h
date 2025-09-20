/* File: plane.h */

#include <iostream>

#include "component.h"

const int num_of_equipComp = 3;						// how many EquipmentCompartments will the plane have

using namespace std;

class Plane : public Object {

	private:
		String title;
		int capacity;
		CargoBay* carBay;
		EquipmentCompartment* equipComp[num_of_equipComp];	// array to EquipmentCompartment *
		PassengerCompartment* passComp;

	public:
		Plane(string, int);
		~Plane();
		String *get_title();
		int get_capacity() const;
		CargoBay *get_carBay();
		EquipmentCompartment **get_equipComp();			// returns pointer to array of pointers
		PassengerCompartment *get_passComp();
		void process(SecurityEmployee *);
		void process(MaintenanceEmployee *);
		void process(CleaningEmployee *);
		void ready_check();
		Plane *clone();
		int equal(Object *);
		String toString();
};
