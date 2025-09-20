import React, { useState } from "react";
import './Login.css';

export default function Login() {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [loginError, setLoginError] = useState(false);

    const userPasswordPairs = [
        { username: "user1", password: "password1" },
        { username: "user2", password: "password2" },
        { username: "user3", password: "password3" },
    ];

    const handleUsernameChange = (e) => {
        setUsername(e.target.value);
    };

    const handlePasswordChange = (e) => {
        setPassword(e.target.value);
    };

    const handleLogin = () => {
        const validPair = userPasswordPairs.find(
            pair => pair.username === username && pair.password === password
        );

        if (validPair) {
            window.location.href = "/student/mainpage";
        } else {
            setLoginError(true);
        }
    };

    return (
        <div className="Login">
            <div className="LeftSection">
                <h1>Καλώς ήρθατε στο <div className="MyStudies">MyStudies</div></h1>
                <h2>Εδώ μπορείτε να:</h2>
                <ul>
                    <li>Βρείτε Πληροφορίες για Μαθήματα</li>
                    <li>Δείτε και να Εκτυπώσετε την Βαθμολογία σας</li>
                    <li>Κάνετε Δήλωση Μαθημάτων</li>
                    <li>Υποβάλετε Αίτηση για Πιστοποιητικά</li>
                </ul>
            </div>
            <div className="RightSection">
                <input
                    type="text"
                    placeholder="Ονοματεπώνυμο"
                    value={username}
                    onChange={handleUsernameChange}
                />
                <input
                    type="password"
                    placeholder="Κωδικός"
                    value={password}
                    onChange={handlePasswordChange}
                />
                <button className="LoginButton" onClick={handleLogin}>
                    Εισοδος
                </button>
                {loginError && <p className="ErrorMessage">Λάθος όνομα χρήστη ή κωδικός</p>}
            </div>
        </div>
    );
}
