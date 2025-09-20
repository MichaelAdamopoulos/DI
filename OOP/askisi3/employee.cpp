/* File: employee.cpp */

#include <iostream>
#include <string>

#include "component.h"

using namespace std;

Employee::Employee(string name) : name(name) {
	cout << "Employee just created!" << endl;
}

Employee::~Employee() {
	cout << "Employee to be destroyed!" << endl;
}

SecurityEmployee::SecurityEmployee(string name) : Employee(name) {
	cout << "SecurityEmployee just created!" << endl;
}

SecurityEmployee::~SecurityEmployee() {
	cout << "SecurityEmployee to be destroyed!" << endl;
}

MaintenanceEmployee::MaintenanceEmployee(string name) : Employee(name) {
	cout << "MaintenanceEmployee just created!" << endl;
}

MaintenanceEmployee::~MaintenanceEmployee() {
	cout << "MaintenanceEmployee to be destroyed!" << endl;
}

CleaningEmployee::CleaningEmployee(string name) : Employee(name) {
	cout << "CleaningEmployee just created!" << endl;
}

CleaningEmployee::~CleaningEmployee() {
	cout << "CleaningEmployee to be destroyed!" << endl;
}

void SecurityEmployee::workOn(PassengerCompartment *passComp) {
	cout << "SecurityEmployee with ID = " << this->id << " will work on PassengerCompartment with ID = " << passComp->get_id() << "!" << endl;
	passComp->isSecure();
	this->passComp++;
}

void SecurityEmployee::workOn(EquipmentCompartment *equipComp) {
	cout << "SecurityEmployee with ID = " << this->id << " will work on EquipmentCompartment with ID = " << equipComp->get_id() << "!" << endl;
	equipComp->isSecure();
	this->equipComp++;
}

void SecurityEmployee::workOn(CargoBay *carBay) {
	cout << "SecurityEmployee with ID = " << this->id << " will work on CargoBay with ID = " << carBay->get_id() << "!" << endl;
	carBay->isSecure();
	this->carBay++;
}

void CleaningEmployee::workOn(PassengerCompartment *passComp) {
	cout << "CleaningEmployee with ID = " << this->id << " will work on PassengerCompartment with ID = " << passComp->get_id() << " !" << endl;
	passComp->isClean();
	this->passComp++;
}

void CleaningEmployee::workOn(CargoBay *carBay) {
	cout << "CleaningEmployee with ID = " << this->id << " will work on CargoBay with ID = " << carBay->get_id() << "!" << endl;
	carBay->isClean();
	this->carBay++;
}

void CleaningEmployee::workOn(EquipmentCompartment *mainComp) {
	// do nothing cause CleaningEmployee does not work on EquipmentCompartments
}

void MaintenanceEmployee::workOn(EquipmentCompartment *equipComp) {
	cout << "MaintenanceEmployee with ID = " << this->id << " will work on EquipmentCompartment with ID = " << equipComp->get_id() << "!" << endl;
	equipComp->isMain();
	this->equipComp++;
}

void MaintenanceEmployee::workOn(CargoBay *carBay) {
	cout << "MaintenanceEmployee with ID = " << this->id << " will work on CargoBay with ID = " << carBay->get_id() << "!" << endl;
	carBay->isMain();
	this->carBay++;
}

void MaintenanceEmployee::workOn(PassengerCompartment *passComp) {
	// do nothing cause MaintenanceEmployee does not work on PassengerCompartmens
}

SecurityEmployee *SecurityEmployee::clone() {
	SecurityEmployee *newSecur = new SecurityEmployee(this->name.get_string());
	newSecur->passComp = this->passComp;
	newSecur->equipComp = this->equipComp;
	newSecur->carBay = this->carBay;
	newSecur->id = this->id;
	newSecur->name = *this->name.clone();
	return newSecur;
}

MaintenanceEmployee *MaintenanceEmployee::clone() {
	MaintenanceEmployee *newMain = new MaintenanceEmployee(this->name.get_string());
	newMain->passComp = this->passComp;
    newMain->equipComp = this->equipComp;
    newMain->carBay = this->carBay;
	newMain->id = this->id;
	newMain->name = *this->name.clone();
	return newMain;
}

CleaningEmployee *CleaningEmployee::clone() {
	CleaningEmployee *newClean = new CleaningEmployee(this->name.get_string());
	newClean->passComp = this->passComp;
    newClean->equipComp = this->equipComp;
    newClean->carBay = this->carBay;
	newClean->id = this->id;
	newClean->name = *this->name.clone();
	return newClean;
}

int SecurityEmployee::equal(Object *sEmp) {				// casting Object * to SecurityEmployee * so we can access SecurityEmployee's data-members
	if ( dynamic_cast<SecurityEmployee *>(sEmp) == NULL )		// if cast fails return 0(not equal)
		return 0;
	if ( this->id == dynamic_cast<SecurityEmployee *>(sEmp)->id )
		if ( this->name.equal(&dynamic_cast<SecurityEmployee *>(sEmp)->name) == 1 )
			if ( this->passComp == dynamic_cast<SecurityEmployee *>(sEmp)->passComp )
				 if ( this->equipComp == dynamic_cast<SecurityEmployee *>(sEmp)->equipComp )
					 if ( this->carBay == dynamic_cast<SecurityEmployee *>(sEmp)->carBay )
						return 1;
	return 0;
}

int MaintenanceEmployee::equal(Object *mEmp) {				// casting similarly
	if ( dynamic_cast<MaintenanceEmployee *>(mEmp) == NULL )
		return 0;
	if ( this->id == dynamic_cast<MaintenanceEmployee *>(mEmp)->id )
		if ( this->name.equal(&dynamic_cast<MaintenanceEmployee *>(mEmp)->name) == 1)
			if ( this->passComp == dynamic_cast<MaintenanceEmployee *>(mEmp)->passComp )
				if ( this->equipComp == dynamic_cast<MaintenanceEmployee *>(mEmp)->equipComp )
					if ( this->carBay == dynamic_cast<MaintenanceEmployee *>(mEmp)->carBay )
						return 1;
	return 0;
}

int CleaningEmployee::equal(Object *cEmp) {				// casting similarly
	if ( dynamic_cast<CleaningEmployee *>(cEmp) == NULL )
		return 0;
	if ( this->id == dynamic_cast<CleaningEmployee *>(cEmp)->id )
		if ( this->name.equal(&dynamic_cast<CleaningEmployee *>(cEmp)->name) == 1)
			if ( this->passComp == dynamic_cast<CleaningEmployee *>(cEmp)->passComp )
				if ( this->equipComp == dynamic_cast<CleaningEmployee *>(cEmp)->equipComp )
					if ( this->carBay == dynamic_cast<CleaningEmployee *>(cEmp)->carBay )
						return 1;
	return 0;
}

String Employee::toString() {						// Employee's toString return a String with Object's toString plus the rest data-members
	return String("Employee: " + Object::toString().get_string() + ", name = " + this->name.toString().get_string() + ", carBay = " + std::to_string(this->carBay) + ", equipComp = " + std::to_string(this->equipComp) + ", passComp = " + std::to_string(this->passComp));
}

									// each class' toString returns Employee's toString plus a description of the current class(Cleaning/Security/Maintenance Employee)

String CleaningEmployee::toString() {
	return("CleaningEmployee: " + Employee::toString().get_string());
}

String SecurityEmployee::toString() {
	return("SecurityEmployee: " + Employee::toString().get_string());
}

String MaintenanceEmployee::toString() {
	return("MaintenanceEmployee: " + Employee::toString().get_string());
}

void CleaningEmployee::report() {
	cout << "CleaningEmployee with ID = " << this->id << " has cleaned " << this->carBay << " CargoBays and " << this->passComp << " PassengerCompartments!" << endl;
}

void MaintenanceEmployee::report() {
	cout << "MaintenanceEmployee with ID = " << this->id << " has maintained " << this->carBay << " CargoBays and " << this->equipComp << " EquipmentCompartments!" << endl;
}

void SecurityEmployee::report() {
	cout << "SecurityEmployee with ID = " << this->id << " has secured " << this->carBay << " CargoBays and " << this->passComp << " PassengerCompartments and " << this->equipComp << " EquipmentCompartments!" << endl;
}

int Employee::get_passComp() {
	return this->passComp;
}

int Employee::get_carBay() {
	return this->carBay;
}

int Employee::get_equipComp() {
	return this->equipComp;
}

String Employee::get_name() {
	return this->name;
}
