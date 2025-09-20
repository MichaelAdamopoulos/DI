// File: PlaneComponent.java

package askisi4;

public abstract class PlaneComponent {

    protected boolean secure;   // boolean functions depending on whether the component is clean, secure or maintained
    protected boolean clean;
    protected boolean main;

    public PlaneComponent() {
        this.secure = false;
        this.clean = false;
        this.main = false;
        System.out.println("PlaneComponent just created!");
    }

    public void isSecure() {
        this.secure = true;
    }

    public void isClean() {
        this.clean = true;
    }

    public void isMain() {
        this.main = true;
    }

    public abstract boolean ready_check();

    public abstract void process(Employee emp);

    @Override
    public String toString() {
        return "PlaneComponent: secure = " + this.secure + ", clean = " + this.clean + ", main = " + this.main;
    }

    @Override
    public abstract boolean equals(Object obj);

    @Override
    public abstract Object clone();
}
