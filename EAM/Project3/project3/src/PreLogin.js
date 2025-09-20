import {Link} from "react-router-dom"
import './PreLogin.css'

export default function PreLogin() {
    return(
        <div className = "PreLogin">
            <h1 style={{color: 'black'}}>Καλώς ήρθατε στο <span class = "MyStudies"> MyStudies</span></h1>
            <Link className = "Link" to = "/professor/login"> ΚΑΘΗΓΗΤΗΣ </Link>
            <Link className = "Link" to = "/student/login"> ΜΑΘΗΤΗΣ </Link>
        </div>        
    )
}