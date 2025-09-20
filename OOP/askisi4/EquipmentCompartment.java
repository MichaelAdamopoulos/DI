// File: EquipmentCompartment.java

package askisi4;

public class EquipmentCompartment extends PrivateCompartment {

    public EquipmentCompartment() {
        System.out.println("EquipmentCompartment just created!");
    }

    @Override
    public boolean ready_check() {
        if ( this.main == true && this.secure == true ) {
            System.out.println(this.toString() + " is OK!");
            return true;
        }
        return false;
    }

    @Override
    public void process(Employee emp) {
        emp.workOn(this);
    }

    @Override
    public String toString() {
        return "EquipmentCompartment: " + super.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if ( !(obj instanceof EquipmentCompartment) )   		// check if obj is of EquipmentCompartment type
            return false;                               		// if not return, else check the equality
        if ( this.clean == ((EquipmentCompartment) obj).clean )     	// casting Object to EquipmentCompartment
            if ( this.secure == ((EquipmentCompartment) obj).secure )   // so we can access its data-members
                if ( this.main == ((EquipmentCompartment) obj).main )
                        return true;
        return false;
    }

    @Override
    public Object clone() {
        EquipmentCompartment nEquip = new EquipmentCompartment();
        nEquip.clean = this.clean;
        nEquip.secure = this.secure;
        nEquip.main = this.main;
        return nEquip;
    }
}
