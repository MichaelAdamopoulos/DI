import { Link } from "react-router-dom"
import "./ProfNavBar.css"

export default function ProfNavBar() {
    return (
        <header className="ProfNavBar">
            <img src="../../public/photos/logo.png" alt="Logo" />
            <nav>
                <Link className="ProfUsername" to="/professor/profil"> Ονοματεπώνυμο </Link>
                <Link className="ProfLogout" to="/"> Αποσύνδεση </Link>
                <p>
                    <Link className="ProfLink" to="/professor/mainpage"> ΑΡΧΙΚΗ </Link>
                    <Link className="ProfLink" to="/professor/subjects"> ΜΑΘΗΜΑΤΑ </Link>
                    <Link className="ProfLink" to="/professor/grades"> ΒΑΘΜΟΛΟΓΙΑ </Link>
                </p>
            </nav>
        </header>
    )
}