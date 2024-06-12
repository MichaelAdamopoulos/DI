import {BrowserRouter, Routes, Route} from "react-router-dom";
import PreLogin from "./PreLogin";
import Login from "./Student/Login";
import MainPage from "./Student/MainPage";
import Apply from "./Student/Apply"
import Subjects from "./Student/Subjects"
import Certificates from "./Student/Certificates"
import Profil from "./Student/Profil"
import PrintGrades from "./Student/GradesPrint";
import Grades from "./Student/Grades";
import ProfLogin from "./Professor/ProfLogin";
import ProfMainPage from "./Professor/ProfMainPage";
import ProfProfil from "./Professor/ProfProfil";
import ProfSubjects from "./Professor/ProfSubjects";
import ProfGrades from "./Professor/ProfGrades";
import ProfGradesSubject from "./Professor/ProfGradesSubject";

export default function App() {
  return (
      <BrowserRouter>
          <Routes>
            <Route exact path="/" element = {<PreLogin/>}/>
            <Route exact path="/student/login" element = {<Login/>}/>
            <Route exact path="/professor/login" element={<ProfLogin />} />
            <Route exact path="/student/mainpage" element = {<MainPage/>}/>
            <Route exact path="/student/profil" element = {<Profil/>}/>
            <Route exact path="/student/grades" element = {<Grades/>}/>
            <Route exact path="/student/certificates" element = {<Certificates/>}/>
            <Route exact path="/student/apply" element = {<Apply/>}/>
            <Route exact path="/student/subjects" element = {<Subjects/>}/>
            <Route exact path="/student/grades/print" element = {<PrintGrades/>} />
            <Route exact path="/professor/login" element={<ProfLogin />} />
            <Route exact path="/professor/mainpage" element={<ProfMainPage />} />
            <Route exact path="/professor/profil" element={<ProfProfil />} />
            <Route exact path="/professor/subjects" element={<ProfSubjects />} />
            <Route exact path="/professor/grades" element={<ProfGrades />} />
            <Route exact path="/professor/grades/:subjectName" element= {<ProfGradesSubject/>}/>
          </Routes>
      </BrowserRouter>
    )
}

