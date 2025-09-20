/* File: component.cpp */

#include <iostream>
#include <string>

#include "component.h"

using namespace std;

PlaneComponent::PlaneComponent() {
	cout << "PlaneComponent just created!" << endl;
}

PlaneComponent::~PlaneComponent() {
	cout << "PlaneComponent to be destroyed!" << endl;
}

PassengerCompartment::PassengerCompartment() {				// if extension is false then do not create interior compartment
	cout << "PassengerCompartment just created!" << endl;		// else create new compartment and make extension false
	if ( this->extension == false )					// so that new compartment does not endlessly create new interior
		if ( this->passComp == NULL ) {				// compartments
			return;						// NOTE: extension does not indicate whether interior compartment
		}							// exists or not
	this->extension = false;
	this->passComp = new PassengerCompartment;
}

PassengerCompartment::~PassengerCompartment() {
	if ( this->passComp != NULL )
		delete this->passComp;
	cout << "PassengerCompartment to be destroyed!" << endl;
}

PrivateCompartment::PrivateCompartment() {
	cout << "PrivateCompartment just created!" << endl;
}

PrivateCompartment::~PrivateCompartment() {
	cout << "PrivateCompartment to be destroyed!" << endl;
}

EquipmentCompartment::EquipmentCompartment() {
	cout << "EquipmentCompartment just created!" << endl;
}

EquipmentCompartment::~EquipmentCompartment() {
	cout << "EquipmentCompartment to be destroyed!" << endl;
}

CargoBay::CargoBay() {
	this->equipComp = new EquipmentCompartment;
	cout << "CargoBay just created!" << endl;
}

CargoBay::~CargoBay() {
	delete this->equipComp;
	cout << "CargoBay to be destroyed!" << endl;
}

void PassengerCompartment::process(Employee *emp) {
	emp->workOn(this);
	if ( this->passComp != NULL )
		emp->workOn(this->passComp);
}

void EquipmentCompartment::process(Employee *emp) {
	emp->workOn(this);
}

void CargoBay::process(Employee *emp) {
	emp->workOn(this);
	emp->workOn(this->equipComp);
}

void PlaneComponent::isSecure() {
	this->secure = true;
}

void PlaneComponent::isClean() {
	this->clean = true;
}

void PlaneComponent::isMain() {
	this->main = true;
}

bool CargoBay::ready_check() {
	if ( this->equipComp->ready_check() == false )
		return false;
	if ( this->secure == true && this->main == true && this->clean == true ) {
		cout << "CargoBay with ID = " << this->id << " is OK!" << endl;
		return true;
	}
	return false;
}

bool EquipmentCompartment::ready_check() {
	if ( this->secure == true && this->main == true ) {
		cout << "EquipmentCompartment with ID = " << this->id << " is OK!" << endl;
		return true;
	}
	return false;
}

bool PassengerCompartment::ready_check() {
	if ( this->passComp != NULL )
		if ( this->passComp->ready_check() == false )
			return false;
	if ( this->clean == true && this->secure == true ) {
		cout << "PassengerCompartment with ID = " << this->id << " is OK!" << endl;
		return true;
	}
	return false;
}

PassengerCompartment *PassengerCompartment::clone() {
	PassengerCompartment *newPass = new PassengerCompartment;
	newPass->main = this->main;
	newPass->secure = this->secure;
	newPass->clean = this->clean;
	newPass->id = this->id;
	if ( this->passComp != NULL )
		newPass->passComp = this->passComp->clone();
	return newPass;
}

EquipmentCompartment *EquipmentCompartment::clone() {
	EquipmentCompartment *newEquip = new EquipmentCompartment;
	newEquip->clean = this->clean;
	newEquip->secure = this->secure;
	newEquip->main = this->main;
	newEquip->id = this->id;
	return newEquip;
}

CargoBay *CargoBay::clone() {
	CargoBay *newCar = new CargoBay;
	newCar->secure = this->secure;
	newCar->main = this->main;
	newCar->clean = this->clean;
	newCar->id = this->id;
	newCar->equipComp = this->equipComp->clone();
	return newCar;
}

int PassengerCompartment::equal(Object *pComp) {			// casting Object * to PassengerCompartment * so we can access PassengerCompartment's data-members
	if ( dynamic_cast<PassengerCompartment *>(pComp) == NULL )	// if casting fails return 0(not equal)
		return 0;
	if ( this->passComp != NULL && dynamic_cast<PassengerCompartment *>(pComp)->passComp != NULL) {
		if ( this->passComp->equal(dynamic_cast<PassengerCompartment *>(pComp)->passComp) == 1)
			return 1;
		else
			return 0;
	}
	else if ( this->passComp != dynamic_cast<PassengerCompartment *>(pComp)->passComp )
		return 0;
	else {
		if ( this->id == dynamic_cast<PassengerCompartment *>(pComp)->id )
			if ( this->clean == dynamic_cast<PassengerCompartment *>(pComp)->clean )
				if ( this->main == dynamic_cast<PassengerCompartment *>(pComp)->main )
					if ( this->secure == dynamic_cast<PassengerCompartment *>(pComp)->secure )
						if ( this->extension == dynamic_cast<PassengerCompartment *>(pComp)->extension )
							return 1;
		return 0;
	}
}

int EquipmentCompartment::equal(Object *eComp) {			// casting similarly
	if ( dynamic_cast<EquipmentCompartment *>(eComp) == NULL )
		return 0;
	if ( this->id == dynamic_cast<EquipmentCompartment *>(eComp)->id )
		if ( this->secure == dynamic_cast<EquipmentCompartment *>(eComp)->secure )
			if ( this->clean == dynamic_cast<EquipmentCompartment *>(eComp)->clean )
				if ( this->main == dynamic_cast<EquipmentCompartment *>(eComp)->main )
					return 1;
	return 0;
}

int CargoBay::equal(Object *cBay) {					// casting similarly
	if ( dynamic_cast<CargoBay *>(cBay) == NULL )
		return 0;
	if ( this->id == dynamic_cast<CargoBay *>(cBay)->id )
		if ( this->main == dynamic_cast<CargoBay *>(cBay)->main )
			if ( this->clean == dynamic_cast<CargoBay *>(cBay)->clean )
				if ( this->secure == dynamic_cast<CargoBay *>(cBay)->secure )
					if ( this->equipComp->equal(dynamic_cast<CargoBay *>(cBay)->equipComp) == 1 )
						return 1;
	return 0;
}

String PlaneComponent::toString() {					// PlaneComponent's toString creates a String of Object's toString plus the rest of its data-members
	return String("PlaneComponent: " + Object::toString().get_string() + ", secure = " + ((this->secure == 0) ? "false":"true") + ", clean = " + ((this->clean == 0) ? "false":"true") + ", main = " + ((this->main == 0) ? "false":"true"));
}

									// each other toString calls its superclass' toString plus the rest of its data-members

String PrivateCompartment::toString() {
	return String("PrivateCompartment: " + PlaneComponent::toString().get_string());
}

String PassengerCompartment::toString() {
	if ( this->passComp == NULL )
		return String("PassengerCompartment: " + PlaneComponent::toString().get_string() + ", extension = " + ((this->extension == 0) ? "false":"true") + ", passComp = NULL");
	return String("PassengerCompartment: " + PlaneComponent::toString().get_string() + ", extension = " + ((this->extension == 0) ? "false":"true") + ", passComp = " + this->passComp->toString().get_string());
}

String EquipmentCompartment::toString() {
	return String("EquipmentCompartment: " + PrivateCompartment::toString().get_string());
}

String CargoBay::toString() {
	return String("CargoBay: " + PrivateCompartment::toString().get_string() + ", equipComp = " + this->equipComp->toString().get_string());
}

bool PlaneComponent::getSecure() {
	return this->secure;
}

bool PlaneComponent::getClean() {
	return this->clean;
}

bool PlaneComponent::getMain() {
	return this->main;
}

PassengerCompartment *PassengerCompartment::get_passComp() {
	return this->passComp;
}

bool PassengerCompartment::get_extension() {
	return this->extension;
}

EquipmentCompartment *CargoBay::get_equipComp() {
	return this->equipComp;
}
