import NavBar from "./NavBar"
import HelpBar from "./HelpBar"

export default function MainPage() {
    return (
        <div className = "MainPage">
            <NavBar/>
            <div style={{ textAlign: 'center', marginTop: '200px' }}>
                <h2>
                    ΕΠΙΛΕΞΤΕ ΜΙΑ ΕΝΕΡΓΕΙΑ ΓΙΑ ΝΑ ΣΥΝΕΧΙΣΕΤΕ
                </h2>
            </div>
            <HelpBar/>
        </div>
    )
}