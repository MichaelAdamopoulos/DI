// File: CleaningEmployee.java

package askisi4;

public class CleaningEmployee extends Employee {

    public CleaningEmployee(String name) {
        super(name);
        System.out.println("CleaningEmployee just created!");
    }

    @Override
    public void report() {
        System.out.println("CleaningEmployee has cleaned " + this.carBay +  " CargoBays and " + this.passComp + " PassengerCompartments!");
    }

    @Override
    public void workOn(CargoBay carBay) {
        System.out.println("CleaningEmployee will work on CargoBay!");
        carBay.isClean();
        this.carBay++;
    }

    @Override
    public void workOn(EquipmentCompartment equipComp) {
        // do nothing cause CleaningEmployee does not work on EquipmentCompartments
    }

    @Override
    public void workOn(PassengerCompartment passComp) {
        System.out.println("CleaningEmployee will work on PassengerCompartment!");
        passComp.isClean();
        this.passComp++;
    }

    @Override
    public String toString() {
        return "CleaningEmployee: " + super.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof CleaningEmployee) )   			// check if obj is of CleaningEmployee type
            return false;                           			// if not return, else check the equality
        if ( this.name.equals(((CleaningEmployee) obj).name) == true )  // casting Object to CleaningEmployee
            if ( this.carBay == ((CleaningEmployee) obj).carBay )       // so we can access its data-members
                if ( this.passComp == ((CleaningEmployee) obj).passComp )
                    if ( this.equipComp == ((CleaningEmployee) obj).equipComp )
                        return true;
        return false;
    }

    @Override
    public Object clone() {
        CleaningEmployee nClean = new CleaningEmployee(this.name);
        nClean.carBay = this.carBay;
        nClean.passComp = this.passComp;
        nClean.equipComp = this.equipComp;
        return nClean;
    }
}
