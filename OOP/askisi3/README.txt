File: README

AM: 1115201800003

Name: Adamopoulos Michael

Exercise 3 contains following files:

- main.cpp
- object.cpp
- object.h
- string.cpp
- string.h
- plane.cpp
- plane.h
- component.cpp
- component.h
- employee.cpp
- employee.h
- makefile

For compilation use the following commands(2 options):

- make run clean

- g++ -g -std=c++11 -c main.cpp object.cpp string.cpp plane.cpp component.cpp employee.cpp
  g++ -g -std=c++11 -o main main.o object.o string.o plane.o component.o employee.o
  ./main

More details:

- main.cpp:

	This file contains a const plane_capacity variable which is passed as argument to the constructor of the plane.
	The boolean variable extension determines whether the PassengerCompartment will have an interior one and is true by default.

- object.h / object.cpp

	Those files contain the implementation of the Object abstract class. Some functions are pure virtual because we want
		every subclass to override them. Identical function is not virtual tho and it's the same for all the subclasses
		because it deals with memory, comparing 'this'.
	There is a static int variable. It's initialized to 1 and represents each Object's id. When an Object is created, it's
		id is initialized from this static variable and then the static variable is raised by 1 for the next Object.
		In this way no 2 Objects can have the same ID(except if they are clones).

- plane.h / plane.cpp

	Those files contain the implementation of the Plane class.
	They contain a const int num_of_equipComp. It represents the number of EquipmentCompartments that the Plane has.
		For the purposes of this exercise it is initialized with 3, but the implementation works the same with
		any number of EquipmentCompartments.
	Because the Plane contains 3 EquipmentCompartments, it has as a data-member an array of EquipmentCompartments.
	Plane has 3 process functions, one for each Employee, which call the process functions of its Components.

- component.h / component.cpp

	Those files contain the implementation of the PlaneComponent abstract class and its subclasses.
		Because PlaneComponent is abstract, most functions are pure virtual.
	PlaneComponent has 3 boolean variables, to represent whether the Component has been cleaned, secured or maintained.
		The accessors and mutators of those variable are not virtual because they can apply to every subclass.
	There is only one process function with argument Employee *. We do not want 3 different functions for every Employee.
		Inside the body of the process function, the workOn function is called and it is then determined which workOn
		and for what Employee type.
	PassengerCompartment contains 2 extra variables: a static boolean extension and a PassengerCompartment *passComp.
		The initial value of the extension variable determines whether there exists an interior PassengerCompartment.
		If it's false, create no interior. But if it's true, create one and make the variable false so the interior
		Compartment does not keep on creating more interior ones. Hence the static keyword.

- employee.h / employee.cpp

	Those files contain the implementation of the Employee abstract class and its subclasses.
		Because Employee is abstract, most functions are pure virtual, except the accessors.
	Employee has 3 int variables to represent how many areas of the Plane has each Employee worked on. Initially 0.
	There are 3 workOn functions, one for each PlaneComponent. They are implemented in a way thay allow for example
		a CleaningEmployee to work on a EquipmentCompartment but it can not make the EquipmentCompartment clean
		and those functions are never called within this exercise.

More details about process-workOn functions:

	Basically main calls 3 Plane's 'process' for every Employee. Each Plane's 'process' calls its Compartment's 'process'
		based on where each Employee works. After, each Compartment's 'process' calls Employee's 'workOn' for this
		Compartment. Which 'workOn' is called is based on the type of the Employee. Then the 'workOn' calls the
		PlaneComponenet's functions 'isSecure/isClean/isMain' and raises the Employee's variables 
		'passComp/carBay/equipComp' by 1 based and what Employee worked where.

More details about equal function:

	Object's equal is pure virtual and is implemented in every subclass. Because Object's equal needs to be pure virtual
		it must have the same definition for every subclass, hence equal(Object *). For that reason, in every
		subclass' equal, we do a dynamic cast from Object * to 'this class' * so we can access this class' data-members.

More details about toString functions:

	Object's toString is virtual and is implemented in all classes. Object's(base class) toString converts its ID to String.
		Thereafter every other subclass converts to String its extra data-members and creates a new String which consists of
		its superclasses toString plus its extra data-member's String.
		
