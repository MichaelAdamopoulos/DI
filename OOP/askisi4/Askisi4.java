// File: Askisi4.java

package askisi4;

public class Askisi4 {

    public static void main(String[] args) {

        System.out.println("Let's create a Plane!");

        Plane myplane = new Plane("myplane",100);

        System.out.println("Let's create some Employees!");

        CleaningEmployee cleaner = new CleaningEmployee("cleaner");
        MaintenanceEmployee maintainer = new MaintenanceEmployee("maintainer");
        SecurityEmployee security = new SecurityEmployee("security");

        System.out.println("Let's have those Employees work on the Plane!");

        myplane.process(cleaner);
        myplane.process(maintainer);
        myplane.process(security);

        System.out.println("Let's have those Employees report back on their work!");

        cleaner.report();
        maintainer.report();
        security.report();

        System.out.println("Let's check if the Plane is ready to take off!");

        myplane.ready_check();
    }
}
