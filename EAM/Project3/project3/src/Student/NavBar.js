import { Link } from "react-router-dom"
import './NavBar.css'

export default function NavBar() {
    return (
        <header className = "NavBar">
            <img src = "../../public/photos/logo.png" alt = "Logo"/>
            <nav>
                <Link className = "Username" to = "/student/profil"> Ονοματεπώνυμο </Link>
                <Link className = "Logout"  to = "/"> Αποσύνδεση </Link>
                <p>
                    <Link className = "Link" to = "/student/mainpage"> ΑΡΧΙΚΗ </Link>
                    <Link className = "Link" to= "/student/subjects"> ΜΑΘΗΜΑΤΑ </Link>
                    <Link className = "Link" to= "/student/apply"> ΔΗΛΩΣΗ </Link>
                    <Link className = "Link" to= "/student/grades"> ΒΑΘΜΟΛΟΓΙΕΣ </Link>
                    <Link className = "Link" to= "/student/certificates"> ΠΙΣΤΟΠΟΙΗΤΙΚΑ </Link>     
                </p>
            </nav>
        </header>
    )
}