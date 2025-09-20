File: README

AM: 1115201800003

Name: Adamopoulos Michael

Exercise 4(Java) contains the following files:

- Askisi4.java(main)
- Plane.java
- PlaneComponent.java
- PrivateCompartment.java
- PassengerCompartment.java
- EquipmentCompartment.java
- CargoBay.java
- Employee.java
- CleaningEmployee.java
- MaintenanceEmployee.java
- SecurityEmployee.java

All the .java files are contained inside the 'askisi4' Package.

There is one .java file for every class. For that reason all classes are public, so that they can be
instanciated from the outside world. Employee/PlaneComponent/PrivateCompartment classes are abstract.

For compilation use the following commands(from parent directoty):

	javac askisi4/*.java
	java askisi4.Askisi4

More details:

- Plane has 3 process functions, one for each Employee, which call the process functions of its Components.

- PlaneComponent has 3 boolean variables, to represent whether the Component has been cleaned, secured or maintained.
	The mutators of those variable are not abstract because they can apply to every subclass.

- PlaneComponent: There is only one process function with argument Employee. We do not want 3 different functions for every Employee.
	Inside the body of the process function, the workOn function is called and it is then determined which workOn
	and for what Employee type.

- PassengerCompartment contains 2 extra variables: a static boolean extension and a PassengerCompartment passComp.
	The initial value of the extension variable determines whether there exists an interior PassengerCompartment.
	If it's false, create no interior. But if it's true, create one and make the variable false so the interior
	Compartment does not keep on creating more interior ones. Hence the static keyword.
	NOTE: extension variable does not indicate whether interior compartment exists or not.

- Employee has 3 int variables to represent how many areas of the Plane has each Employee worked on. Initialized to 0 inside the constructor.

- There are 3 workOn functions, one for each PlaneComponent. They are implemented in a way thay allow for example
	a CleaningEmployee to work on a EquipmentCompartment but it can not make the EquipmentCompartment clean
	and those functions are never called within this exercise.

- More details about process-workOn functions:

	Basically main calls 3 Plane's 'process' for every Employee. Each Plane's 'process' calls its Compartment's 'process'
		based on where each Employee works. After, each Compartment's 'process' calls Employee's 'workOn' for this
		Compartment. Which 'workOn' is called is based on the type of the Employee. Then the 'workOn' calls the
		PlaneComponenet's functions 'isSecure/isClean/isMain' and raises the Employee's variables 
		'passComp/carBay/equipComp' by 1 based and what Employee worked where.

- Object's equals is overrided by every subclass. So every subclass' equals function must have the same definition with Object's equals, hence equals(Object obj).
	For that reason, in every subclass' equals, we do a cast from Object to 'this class' so we can access this class' data-members.
	
- Object's toString is overrided by every subclass. Every subclass converts to String its extra data-members and creates a new String which consists of
		its superclass' toString plus its extra data-member's String.

- Object's clone is overrided by every subclass.

	


