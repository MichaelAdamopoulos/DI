import ProfNavBar from "./ProfNavBar"
import ProfProfilDropdown from './ProfProfilDropdown';
import ProfHelpBar from './ProfHelpBar'

export default function ProfProfil() {

    const about = [
        {title: "ΑΚΑΔΗΜΑΙΚΗ ΤΑΥΤΟΤΗΤΑ", info: "12563", id: 1, edit: "false"},
        {title: "ΤΜΗΜΑ", info: "ΠΛΗΡΟΦΟΡΙΚΗΣ", id: 2, edit: "false"},
        {title: "ΒΑΘΜΙΔΑ", info: "ΑΕΙ", id: 3, edit: "false"},
        {title: "ΘΕΣΗ", info: "ΚΑΘΗΓΗΤΡΙΑ", id: 4, edit: "false"}
    ];
    
    const personal = [
        {title: "ΌΝΟΜΑ", info: "ΕΜΜΑΝΟΥΕΛΑ", id: 5, edit: "false"},
        {title: "ΕΠΩΝΥΜΟ", info: "ΠΑΠΑΔΟΠΟΥΛΟΥ", id: 6, edit: "false"},
        {title: "ΟΝΟΜΑ ΠΑΤΕΡΑ", info: "ΜΑΡΙΟΣ", id: 7, edit: "false"},
        {title: "ΟΝΟΜΑ ΜΗΤΕΡΑΣ", info: "ΜΑΡΙΑΛΕΝΝΑ", id: 8, edit: "false"},
        {title: "ΗΜΕΡΟΜΗΝΙΑ ΓΕΝΝΗΣΗΣ", info: "1.1.1990", id: 9, edit: "false"},
        {title: "ΟΙΚΟΓΕΝΕΙΑΚΗ ΚΑΤΑΣΤΑΣΗ", info: "ΑΝΥΠΑΝΤΡΗ", id: 10, edit: "false"},
        {title: "ΠΟΛΗ / ΧΩΡΙΟ ΓΕΝΝΗΣΗΣ", info: "ΑΘΗΝΑ", id: 11, edit: "false"},
        {title: "ΑΡΙΘΜΟΣ ΤΑΥΤΟΤΗΤΑΣ", info: "ΑΚ12345", id: 12, edit: "false"},
        {title: "ΕΚΔΟΥΣΑ ΑΡΧΗ", info: "ΑΘΗΝΑ", id: 13, edit: "false"},
        {title: "ΗΜΕΡΟΜΗΝΙΑ ΕΚΔΟΣΗΣ", info: "1.1.2Ο00", id: 14, edit: "false"},
        {title: "ΑΜΚΑ", info: "1234567890", id: 15, edit: "false"},
        {title: "ΑΦΜ", info: "1234567890", id: 16, edit: "false"},
        {title: "TΙΤΛΟΣ ΠΡΟΣΩΠΟΥ", info: "ΚΑΘΗΓΗΤΡΙΑ", id: 17, edit: "false"},
        {title: "ΔΟΥ", info: "ΚΟΡΩΠΙΟΥ", id: 18, edit: "false"},
        {title: "ΦΥΛΟ", info: "ΘΗΛΥΚΟ", id: 19, edit: "false"},
    ];
    
    const contact = [
        {title: "ΜΟΝΙΜΗ ΔΙΕΥΘΥΝΣΗ ΚΑΤΟΙΚΙΑΣ", info: "ΑΘΗΝΑ", id: 29, edit: "false"},
        {title: "ΜΟΝΙΜΗ ΠΟΛΗ ΚΑΤΟΙΚΙΑΣ", info: "ΑΘΗΝΑ", id: 20, edit: "false"},
        {title: "ΤΗΛΕΦΩΝΟ ΜΟΝΙΜΗΣ ΚΑΤΟΙΚΙΑΣ", info: "1234567890", id: 21, edit: "false"},
        {title: "ΤΚ ΚΩΔΙΚΑΣ ΜΟΝΙΜΗΣ ΚΑΤΟΙΚΙΑΣ", info: "12345", id: 22, edit: "false"},
        {title: "ΠΡΟΣΩΡΙΝΗ ΔΙΕΥΘΥΝΣΗ ΚΑΤΟΙΚΙΑΣ", info: "ΑΘΗΝΑ", id: 23, edit: "false"},
        {title: "ΠΡΟΣΩΡΙΝΗ ΠΟΛΗ ΚΑΤΟΙΚΙΑΣ", info: "ΑΘΗΝΑ", id: 24, edit: "false"},
        {title: "ΤΗΛΕΦΩΝΟ ΠΡΟΣΩΡΙΝΗ ΚΑΤΟΙΚΙΑΣ", info: "1234567890", id: 25, edit: "false"},
        {title: "ΤΚ ΚΩΔΙΚΑΣ ΠΡΟΣΩΡΙΝΗ ΚΑΤΟΙΚΙΑΣ", info: "12345", id: 26, edit: "false"},
        {title: "ΑΡΙΘΜΟΣ ΚΙΝΗΤΟΥ ΤΗΛΕΦΩΝΟΥ", info: "1234567890", id: 27, edit: "true"},
        {title: "ΔΙΕΥΘΥΝΣΗ ΗΛΕΚΤΡΟΝΙΚΟΥ ΤΑΧΥΔΡΟΜΕΙΟΥ", info: "bla@gmail.com", id: 28, edit: "true"}
    ];

    return (
        <div>
            <ProfNavBar/>
            <div className="ProfProfil">
                <ProfProfilDropdown about={about} personal={personal} contact={contact} />
            </div>
            <ProfHelpBar/>
        </div>
    )
}