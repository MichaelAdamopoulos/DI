/* File: component.h */

#include <iostream>

#include "employee.h"

using namespace std;

class PlaneComponent : public Object {

	protected:
		bool secure = false;			// boolean functions depending on whether the component is clean, secure or maintained
		bool clean = false;
		bool main = false;

	public:
		PlaneComponent();
		~PlaneComponent();
		virtual void process(Employee *) = 0;
		virtual bool ready_check() = 0;
		virtual PlaneComponent *clone() = 0;
		virtual int equal(Object *) = 0;
		bool getSecure();
		bool getClean();
		bool getMain();
		void isSecure();
		void isClean();
		void isMain();
		virtual String toString() = 0;
};

class PassengerCompartment : public PlaneComponent {

	private:
		static bool extension;
		PassengerCompartment *passComp = NULL;

	public:
		PassengerCompartment();
		~PassengerCompartment();
		PassengerCompartment *get_passComp();
		bool get_extension();
		void process(Employee *);
		bool ready_check();
		PassengerCompartment *clone();
		int equal(Object *);
		String toString();
};

class PrivateCompartment : public PlaneComponent {

	public:
		PrivateCompartment();
		virtual ~PrivateCompartment();
		virtual void process(Employee *) = 0;
		virtual bool ready_check() = 0;
		virtual PrivateCompartment *clone() = 0;
		virtual int equal(Object *) = 0;
		virtual String toString() = 0;
};

class EquipmentCompartment : public PrivateCompartment {

	public:
		EquipmentCompartment();
		~EquipmentCompartment();
		void process(Employee *);
		bool ready_check();
		EquipmentCompartment *clone();
		int equal(Object *);
		String toString();
};

class CargoBay : public PrivateCompartment {

	private:
		EquipmentCompartment *equipComp;

	public:
		CargoBay();
		~CargoBay();
		EquipmentCompartment *get_equipComp();
		void process(Employee *);
		bool ready_check();
		CargoBay *clone();
		int equal(Object *);
		String toString();
};
