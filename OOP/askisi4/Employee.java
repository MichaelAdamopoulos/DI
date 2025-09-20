// File: Employee.java

package askisi4;

public abstract class Employee {

    protected String name;
    protected int carBay;
    protected int equipComp;
    protected int passComp;

    public Employee(String name) {
        this.name = name;
        this.carBay = 0;        // how many components has an employee cleaned, maintained or secured
        this.equipComp = 0;
        this.passComp = 0;
        System.out.println("Employee just created!");
    }

    public abstract void report();

    public abstract void workOn(CargoBay carBay);

    public abstract void workOn(PassengerCompartment passComp);

    public abstract void workOn(EquipmentCompartment equipComp);

    @Override
    public String toString() {
        return "Employee: name = " + this.name + ", carBay = " + this.carBay + ", equipComp = " + this.equipComp + ", passComp = " + this.passComp;
    }

    @Override
    public abstract boolean equals(Object obj);

    @Override
    public abstract Object clone();
}
