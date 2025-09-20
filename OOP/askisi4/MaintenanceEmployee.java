// File: MaintenanceEmployee.java

package askisi4;

public class MaintenanceEmployee extends Employee {

    public MaintenanceEmployee(String name) {
        super(name);
        System.out.println("MaintenanceEmployee just created!");
    }

    @Override
    public void report() {
        System.out.println("MaintenanceEmployee has maintained " + this.carBay +  " CargoBays and " + this.equipComp + " EquipmentCompartments!");
    }

    @Override
    public void workOn(CargoBay carBay) {
        System.out.println("MaintenanceEmployee will work on CargoBay!");
        carBay.isMain();
        this.carBay++;
    }

    @Override
    public void workOn(EquipmentCompartment equipComp) {
        System.out.println("MaintenanceEmployee will work on EquipmentCompartment!");
        equipComp.isMain();
        this.equipComp++;
    }

    @Override
    public void workOn(PassengerCompartment passComp) {
        // do nothing cause MaintenanceEmployee does not work on PassengerCompartmens
    }

    @Override
    public String toString() {
        return "MaintenanceEmployee: " + super.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof MaintenanceEmployee) ) 				// check if obj is of MaintenanceEmployee type
            return false;                           		 		// if not return, else check the equality
        if ( this.name.equals(((MaintenanceEmployee) obj).name) == true )   	// casting Object to MaintenanceEmployee
            if ( this.carBay == ((MaintenanceEmployee) obj).carBay )        	// so we can access its data-members
                if ( this.passComp == ((MaintenanceEmployee) obj).passComp )
                    if ( this.equipComp == ((MaintenanceEmployee) obj).equipComp )
                        return true;
        return false;
    }

    @Override
    public Object clone() {
        MaintenanceEmployee nMain = new MaintenanceEmployee(this.name);
        nMain.carBay = this.carBay;
        nMain.passComp = this.passComp;
        nMain.equipComp = this.equipComp;
        return nMain;
    }
}
