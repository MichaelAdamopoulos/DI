// File: SecurityEmployee.java

package askisi4;

class SecurityEmployee extends Employee {

     public SecurityEmployee(String name) {
         super(name);
         System.out.println("SecurityEmployee just created!");
     }

     @Override
     public void report() {
        System.out.println("SecurityEmployee has secured " + this.carBay +  " CargoBays and " + this.passComp + " PassengerCompartments and " + this.equipComp + " EquipmentCompartments!");
    }

     @Override
     public void workOn(CargoBay carBay) {
        System.out.println("SecurityEmployee will work on CargoBay!");
        carBay.isSecure();
        this.carBay++;
    }

     @Override
    public void workOn(EquipmentCompartment equipComp) {
        System.out.println("SecurityEmployee will work on EquipmentCompartment!");
        equipComp.isSecure();
        this.equipComp++;
    }

     @Override
    public void workOn(PassengerCompartment passComp) {
        System.out.println("SecurityEmployee will work on PassengerCompartment!");
        passComp.isSecure();
        this.passComp++;
    }

     @Override
    public String toString() {
        return "SecurityEmployee: " + super.toString();
    }

     @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof SecurityEmployee) )       			// check if obj is of SecurityEmployee type
            return false;                 		        		// if not return, else check the equality
        if ( this.name.equals(((SecurityEmployee) obj).name) == true )  	// casting Object to SecurityEmployee
            if ( this.carBay == ((SecurityEmployee) obj).carBay )       	// so we can access its data-members
                if ( this.passComp == ((SecurityEmployee) obj).passComp )
                    if ( this.equipComp == ((SecurityEmployee) obj).equipComp )
                        return true;
        return false;
    }

     @Override
    public Object clone() {
        SecurityEmployee nSecure = new SecurityEmployee(this.name);
        nSecure.carBay = this.carBay;
        nSecure.passComp = this.passComp;
        nSecure.equipComp = this.equipComp;
        return nSecure;
    }
}
