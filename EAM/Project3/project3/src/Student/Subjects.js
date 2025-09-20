import HelpBar from "./HelpBar"
import NavBar from "./NavBar"
import DropdownMenu from "./SubjectsDropdown"

export default function Subjects() {
    return (
        <div className = "Subjects">
            <NavBar/>
            <DropdownMenu />
            <HelpBar/>
        </div>
    )
}

