// File: PrivateCompartment.java

package askisi4;

public abstract class PrivateCompartment extends PlaneComponent {

    public PrivateCompartment() {
        System.out.println("PrivateCompartment just created!");
    }

    @Override
    public abstract boolean ready_check();

    @Override
    public abstract void process(Employee emp);

    @Override
    public String toString() {
        return "PrivateCompartment: " + super.toString();
    }

    @Override
    public abstract boolean equals(Object obj);

    @Override
    public abstract Object clone();
}
