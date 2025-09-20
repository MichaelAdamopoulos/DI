// File: CargoBay.java

package askisi4;

public class CargoBay extends PrivateCompartment {

    EquipmentCompartment equipComp = null;

    public CargoBay() {
        this.equipComp = new EquipmentCompartment();
        System.out.println("CargoBay just created!");
    }

    @Override
    public boolean ready_check() {
        if ( this.clean == true && this.secure == true && this.main == true )
            if ( this.equipComp.ready_check() == true ) {
                System.out.println(this.toString() + " is OK!");
                return true;
            }
        return false;
    }

    @Override
    public void process(Employee emp) {
        emp.workOn(this);
        emp.workOn(this.equipComp);
    }

    @Override
    public String toString() {
        return "CargoBay: " + super.toString() + ", equipComp = " + equipComp.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof CargoBay) )   		 	// check if obj is of CargoBay type
            return false;                  		 	// if not return, else check the equality
        if ( this.clean == ((CargoBay) obj).clean ) 	 	// casting Object to CargoBay
            if ( this.secure == ((CargoBay) obj).secure )	// so we can access its data-members
                if ( this.main == ((CargoBay) obj).main )
                    if ( this.equipComp.equals(((CargoBay) obj).equipComp) == true )
                        return true;
        return false;
    }

    @Override
    public Object clone() {
        CargoBay nBay = new CargoBay();
        nBay.clean = this.clean;
        nBay.secure = this.secure;
        nBay.main = this.main;
        nBay.equipComp = (EquipmentCompartment) this.equipComp.clone();
        return nBay;
    }
}
