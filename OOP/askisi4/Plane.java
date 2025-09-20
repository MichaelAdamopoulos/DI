// File: Plane.java

package askisi4;

public class Plane {

    private String title;
    private int capacity;
    private CargoBay carBay;
    private EquipmentCompartment equipComp[];
    private PassengerCompartment passComp;

    public Plane(String title, int capacity) {
        this.title = title;
        this.capacity = capacity;
        this.carBay = new CargoBay();
        this.equipComp =  new EquipmentCompartment[3];
        for ( int i = 0 ; i < 3 ; i++ )
            this.equipComp[i] = new EquipmentCompartment();
        this.passComp = new PassengerCompartment();
    }

    public String get_title() {
        return this.title;
    }

    public int get_capacity() {
        return this.capacity;
    }

    public CargoBay get_carBay() {
        return this.carBay;
    }

    public PassengerCompartment get_passComp() {
        return this.passComp;
    }

    public EquipmentCompartment[] get_equipComp() {
        return this.equipComp;
    }

    // plane's process calls process of each PlaneComponent depending on the Employee

    public void process(SecurityEmployee sEmp) {
        this.passComp.process(sEmp);
        for ( int i = 0 ; i < 3 ; i++ )
            this.equipComp[i].process(sEmp);
        this.carBay.process(sEmp);
    }

    public void process(CleaningEmployee cEmp) {
        this.passComp.process(cEmp);
        this.carBay.process(cEmp);
    }

    public void process(MaintenanceEmployee mEmp) {
        for ( int i = 0 ; i < 3 ; i++ )
            this.equipComp[i].process(mEmp);
        this.carBay.process(mEmp);
    }

    public void ready_check() {     		// if all PlaneComponents are ready then plane is ready
        for ( int i = 0 ; i < 3 ; i++ )
            if ( this.equipComp[i].ready_check() == false ) {
                System.out.println("Plane not ready to take off!");
                return;
            }
        if ( this.passComp.ready_check() == false || this.carBay.ready_check() == false ) {
            System.out.println("Plane not ready to take off!");
            return;
        }
        System.out.println("Plane ready to take off!");
    }

    @Override
    public String toString() {  		// Plane's toString returns a String which contains each data-member's toString
        return "Plane: title = " + this.title
                + ", capacity = " + this.capacity
                + ", carBay = " + this.carBay.toString()
                + ", equipComp[0-3] = " + this.equipComp[0].toString() + ", "
                + this.equipComp[1].toString() + ", " + this.equipComp[2].toString()
                + ", passComp = " + this.passComp.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof Plane) )          // check if obj is of Plane type
            return false;                       // if not return, else check the equality
        for ( int i = 0 ; i < 3 ; i++ )         // casting Object to Plane so we can access its data-members
            if ( this.equipComp[i].equals(((Plane) obj).equipComp[i]) == false )
                return false;
        if ( this.capacity == ((Plane) obj).capacity )
            if ( this.title.equals(((Plane) obj).title) == true )
                if ( this.carBay.equals(((Plane) obj).carBay) == true )
                    if ( this.passComp.equals(((Plane) obj).passComp) == true )
                        return true;
        return false;
    }

    @Override
    public Object clone() { 			// casting because clone returns Object
        Plane nPlane = new Plane(this.title, this.capacity);
        nPlane.carBay = (CargoBay) this.carBay.clone();
        nPlane.passComp = (PassengerCompartment) this.passComp.clone();
        for ( int i = 0 ; i < 3 ; i ++ )
            nPlane.equipComp[i] = (EquipmentCompartment) this.equipComp[i].clone();
        return nPlane;
    }
}
