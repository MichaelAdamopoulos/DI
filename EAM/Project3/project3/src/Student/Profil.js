import NavBar from "./NavBar"
import ProfilDropdown from './ProfilDropdown';
import HelpBar from './HelpBar'

export default function Profil() {

    const about = [
        {title: "ΗΜΕΡΟΜΗΝΙΑ ΕΓΓΡΑΦΗΣ", info: "1.1.2000", id: 1, edit: "false"},
        {title: "ΕΞΑΜΗΝΟ ΦΟΙΤΗΣΗΣ", info: "5", id: 2, edit: "false"},
        {title: "ΚΑΤΑΣΤΗΑΣΗ ΜΕΡΙΚΗΣ ΦΟΙΤΗΣΗΣ", info: "ΝΑΙ", id: 3, edit: "false"},
        {title: "ΣΥΝΟΛΙΚΑ ECTS", info: "100", id: 4, edit: "false"}
    ];

    const personal = [
        {title: "ΌΝΟΜΑ", info: "ΜΙΧΑΛΗΣ", id: 5, edit: "false"},
        {title: "ΕΠΩΝΥΜΟ", info: "ΑΔΑΜΟΠΟΥΛΟΣ", id: 6, edit: "false"},
        {title: "ΟΝΟΜΑ ΠΑΤΕΡΑ", info: "ΜΙΧΑΛΗΣ", id: 7, edit: "false"},
        {title: "ΟΝΟΜΑ ΜΗΤΕΡΑΣ", info: "ΜΙΧΑΕΛΑ", id: 8, edit: "false"},
        {title: "ΗΜΕΡΟΜΗΝΙΑ ΓΕΝΝΗΣΗΣ", info: "1.1.2000", id: 9, edit: "false"},
        {title: "ΟΙΚΟΓΕΝΕΙΑΚΗ ΚΑΤΑΣΤΑΣΗ", info: "ΑΝΥΠΑΝΤΡΟΣ", id: 10, edit: "false"},
        {title: "ΑΡΙΘΜΟΣ ΑΔΕΛΦΩΝ", info: "1", id: 11, edit: "false"},
        {title: "ΕΚΠΛΗΡΩΣΗΣ ΣΤΡΑΤΙΟΤΙΚΗΣ ΘΗΤΕΙΑΣ", info: "ΟΧΙ", id: 12, edit: "false"},
        {title: "ΠΟΛΗ / ΧΩΡΙΟ ΓΕΝΝΗΣΗΣ", info: "ΑΘΗΝΑ", id: 13, edit: "false"},
        {title: "ΑΡΙΘΜΟΣ ΤΑΥΤΟΤΗΤΑΣ", info: "ΑΚ12345", id: 14, edit: "false"},
        {title: "ΕΚΔΟΥΣΑ ΑΡΧΗ", info: "ΑΘΗΝΑ", id: 15, edit: "false"},
        {title: "ΗΜΕΡΟΜΗΝΙΑ ΕΚΔΟΣΗΣ", info: "1.1.2Ο00", id: 16, edit: "false"},
        {title: "ΑΜΚΑ", info: "1234567890", id: 17, edit: "false"},
        {title: "ΑΦΜ", info: "1234567890", id: 18, edit: "false"}
    ];

    const contact = [
        {title: "ΜΟΝΙΜΗ ΔΙΕΥΘΥΝΣΗ ΚΑΤΟΙΚΙΑΣ", info: "ΑΘΗΝΑ", id: 19, edit: "false"},
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
            <NavBar/>
            <div className = "Profil">
                <ProfilDropdown about = {about} personal = {personal} contact = {contact} />
            </div>
            <HelpBar/>
        </div>
    )
}