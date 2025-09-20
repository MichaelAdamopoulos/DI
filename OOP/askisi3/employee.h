/* File: employee.h */

#include <iostream>
#include <string>

#include "string.h"

class PassengerCompartment;
class EquipmentCompartment;
class CargoBay;

class Employee : public Object {

	protected:
		String name;
		int carBay = 0;			// how many components has an employee cleaned, maintained or secured
		int equipComp = 0;
		int passComp = 0;

	public:
		Employee(string);
		~Employee();
		String get_name();
		int get_carBay();
		int get_equipComp();
		int get_passComp();
		virtual void workOn(PassengerCompartment *) = 0;
		virtual void workOn(EquipmentCompartment *) = 0;
		virtual void workOn(CargoBay *) = 0;
		virtual void report() = 0;
		virtual Employee *clone() = 0;
		virtual int equal(Object *) = 0;
		virtual String toString();
};

class SecurityEmployee : public Employee {

	public:
		SecurityEmployee(string);
		~SecurityEmployee();
		void workOn(PassengerCompartment *);
		void workOn(EquipmentCompartment *);
		void workOn(CargoBay *);
		void report();
		SecurityEmployee *clone();
		int equal(Object *);
		String toString();
};

class MaintenanceEmployee : public Employee {

	public:
		MaintenanceEmployee(string);
		~MaintenanceEmployee();
		void workOn(PassengerCompartment *);
		void workOn(EquipmentCompartment *);
		void workOn(CargoBay *);
		void report();
		MaintenanceEmployee *clone();
		int equal(Object *);
		String toString();
};

class CleaningEmployee : public Employee {

	public:
		CleaningEmployee(string);
		~CleaningEmployee();
		void workOn(PassengerCompartment *);
		void workOn(EquipmentCompartment *);
		void workOn(CargoBay *);
		void report();
		CleaningEmployee *clone();
		int equal(Object *);
		String toString();
};
