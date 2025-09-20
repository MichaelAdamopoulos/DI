/* File: plane.cpp */

#include <iostream>
#include <string>

#include "plane.h"

using namespace std;

Plane::Plane(string title, int capacity) : title(title) , capacity(capacity) {
	this->carBay = new CargoBay;
	for ( int i = 0 ; i < num_of_equipComp ; i++ )
		this->equipComp[i] = new EquipmentCompartment;
	this->passComp = new PassengerCompartment;
	cout << "Plane just created!" << endl;
}

Plane::~Plane() {	// delete all dynamic allocated memory
	for ( int i = 0 ; i < num_of_equipComp ; i++ )
		delete this->equipComp[i];
	delete this->passComp;
	delete this->carBay;
	cout << "Plane to be destroyed!" << endl;
}

String *Plane::get_title() {
	return &this->title;
}

int Plane::get_capacity() const {
	return this->capacity;
}

CargoBay *Plane::get_carBay() {
	return this->carBay;
}

EquipmentCompartment **Plane::get_equipComp() {
	return this->equipComp;
}

PassengerCompartment *Plane::get_passComp() {
	return this->passComp;
}

void Plane::process(SecurityEmployee* securEmployee) {		// plane's process calls process of each PlaneComponent depending on the Employee
	this->passComp->process(securEmployee);
	for ( int i = 0 ; i < num_of_equipComp ; i++ )
		this->equipComp[i]->process(securEmployee);	// work to all EquipmentCompartments
	this->carBay->process(securEmployee);
}

void Plane::process(CleaningEmployee* cleanEmployee) {
	this->passComp->process(cleanEmployee);
	this->carBay->process(cleanEmployee);
}

void Plane::process(MaintenanceEmployee* mainEmployee) {
	for ( int i = 0 ; i < num_of_equipComp ; i++ )
		this->equipComp[i]->process(mainEmployee);
	this->carBay->process(mainEmployee);
}

void Plane::ready_check() {					// if all PlaneComponents are ready then plane is ready
	for ( int i = 0 ; i < num_of_equipComp ; i++ )		// first chech the EquipmentCompartments
		if ( this->equipComp[i]->ready_check() == false ) {
			cout << "Plane not ready to take off!" << endl;
			return;
		}						// then the rest
	if ( this->passComp->ready_check() == false || this->carBay->ready_check() == false ) {
			cout << "Plane not ready to take off!" << endl;
			return;
		}
	cout << "Plane ready to take off!" << endl;
}

Plane *Plane::clone() {
	Plane *newplane = new Plane(this->title.get_string(), this->capacity);
	newplane->id = this->id;
	newplane->title = *this->title.clone();
	newplane->carBay = this->carBay->clone();
	newplane->passComp = this->passComp->clone();
	for ( int i = 0 ; i < num_of_equipComp ; i++ )
		newplane->equipComp[i] = this->equipComp[i]->clone();
	return newplane;
}

int Plane::equal(Object *plane) {				// casting Object * to Plane * so we can access Plane's data-members
	if ( dynamic_cast<Plane *>(plane) == NULL )		// if cast fails then return 0(not equal)
		return 0;
	if ( this->id == dynamic_cast<Plane *>(plane)->id )
		if ( this->title.equal(&dynamic_cast<Plane *>(plane)->title) == 1 )
			if ( this->carBay->equal(dynamic_cast<Plane *>(plane)->carBay) == 1 )
				if ( this->passComp->equal(dynamic_cast<Plane *>(plane)->passComp) == 1 ) {
					for ( int i = 0 ; i < num_of_equipComp ; i++ )
						if ( dynamic_cast<Plane *>(plane)->equipComp[i] == NULL )
							return 0;
						else if ( this->equipComp[i]->equal(dynamic_cast<Plane *>(plane)->equipComp[i]) == 0 )
							return 0;
					return 1;
				}
	return 0;
}

String Plane::toString() {
	String str = String(this->equipComp[0]->toString().get_string());
	String comma = String(", ");
	for ( int i = 1; i < num_of_equipComp ; i++ ) {		// first create a String which contains each EquipmentCompartment's toString
		String *tempstr = new String(this->equipComp[i]->toString());
		str.concat(comma);
		str.concat(*tempstr);
		delete tempstr;
	}							// Plane's toString returns a String which contains each data-member's toString
	return String(Object::toString().get_string() + ", title = " + title.toString().get_string() + ", capacity = " + std::to_string(this->capacity) + ", carBay = " + this->carBay->toString().get_string() + ", passComp = " + this->passComp->toString().get_string() + ", equipComp[0-" + std::to_string(num_of_equipComp-1) + "] = " + str.get_string());
}
