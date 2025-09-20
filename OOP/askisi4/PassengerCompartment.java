// File: PassengerCompartment.java

package askisi4;

public class PassengerCompartment extends PlaneComponent {

    private PassengerCompartment passComp = null;
    private static boolean extension = true;                        	// default value so PassengerCompartment will contain an interior one

    public PassengerCompartment() {                                 	// if extension is false then do not create interior compartment
        System.out.println("PassengerCompartment just created!");  	// else create new compartment and make extension false
        if ( this.extension == false )                              	// so that new compartment does not endlessly create new interior
            if ( this.passComp == null )                            	// compartments
                return;                                             	// NOTE: extension does not indicate whether interior compartment
        this.extension = false;                                     	// exists or not
        passComp = new PassengerCompartment();
    }

    @Override
    public boolean ready_check() {
        if ( this.passComp != null)
            if ( this.passComp.ready_check() == false )
                return false;
        if ( this.clean == true && this.secure == true ) {
            System.out.println(this.toString() + " is OK!");
            return true;
        }
        return false;
    }

    @Override
    public void process(Employee emp) {
        emp.workOn(this);
        if ( this.passComp != null )
            emp.workOn(this.passComp);
    }

    @Override
    public String toString() {
        if ( this.passComp == null )
            return "PassengerCompartment: " + super.toString() + ", extension = " + this.extension + ", passComp = null";
        return "PassengerCompartment: " + super.toString() + ", extension = " + this.extension + ", passComp = " + passComp.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof PassengerCompartment) )   		// check if obj is of PassengerCompartment type
            return false;                               		// if not return, else check the equality
        if ( this.passComp != null ) {
            if ( ((PassengerCompartment) obj).passComp == null )    	// casting Object to PassengerCompartment
                return false;                                       	// so we can access its data-members
            if ( this.passComp.equals(((PassengerCompartment) obj).passComp) == false )
                return false;
        }
        if ( this.clean == ((PassengerCompartment) obj).clean )
            if ( this.secure == ((PassengerCompartment) obj).secure )
                if ( this.main == ((PassengerCompartment) obj).main )
                        return true;
        return false;
    }

    @Override
    public Object clone() {
        PassengerCompartment nPass = new PassengerCompartment();
        nPass.clean = this.clean;
        nPass.secure = this.secure;
        nPass.main = this.main;
        if ( this.passComp != null )
            nPass.passComp = (PassengerCompartment) this.passComp.clone();
        return nPass;
    }
}
