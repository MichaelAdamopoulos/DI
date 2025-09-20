import React, { useState } from 'react';
import './AppButtonStyles.css';
import ApplySubjectListWithCheckBox from './Apply_SubjectListWithCheckBox'
import ApplySemesterTree from './Apply_SemesterTree';

const InfoPage = () => {
  const [state, setState] = useState(0);
  const infoList = ["ΧΩΡΙΣ ΔΗΛΩΣΗ", "ΠΡΟΣΩΡΙΝΗ ΔΗΛΩΣΗ", "ΟΡΙΣΤΙΚΟΠΟΙΗΜΕΝΗ ΔΗΛΩΣΗ"];
  const [currentPage, setCurrentPage] = useState(1);
  const [selectedSubjects, setSelectedSubjects] = useState({});
  const [errorMessage, setErrorMessage] = useState('');
  const [areSubSelected, setAreSubSelected] = useState(false);

  const OldSubjects = [
        { name: 'Διακριτά', ects: 5, code: 'ΔΙΑ101', semester: 'Εξάμηνο 1' },
        { name: 'Εισαγωγή στον Προγραμματισμός', ects: 4, code: 'ΕΙΣ103', semester: 'Εξάμηνο 1'},
        { name: 'ΕΑΜ', ects: 6, code: 'ΕΑΜ702', semester: 'Εξάμηνο 7' },
  ];

  const handleHistoryPage = () => {
    setCurrentPage(10);
  }

  const handleReturnClick = () => {
    setCurrentPage(1);
  }

  const handleEditPage = () => {
    setCurrentPage(5);
  }

  const handleNextPage = () => {
    setCurrentPage(currentPage + 1);
  }

  const handlePreviousPage = () => {
    setCurrentPage(currentPage - 1);
  }

  const handleClickedItems = () => {
    setCurrentPage(currentPage + 1);
  }

  const handleSavedClick = () => {
    if (selectedSubjects.length > 0) {
      setCurrentPage(4);
      setState(1);
      setAreSubSelected(true);
      setErrorMessage('');
    } else {
      setErrorMessage('Πρέπει να επιλέξετε τουλάχιστον ένα μάθημα.');
      setAreSubSelected(false);
    }
  };
  
  const handleFinalApply = () => {
    if (selectedSubjects.length > 0) {
      setCurrentPage(20);
      setState(2);
      setAreSubSelected(true);
    } else {
      setErrorMessage('Πρέπει να επιλέξετε τουλάχιστον ένα μάθημα.');
      setAreSubSelected(false);
    }
  };

  const handleSubjectChange = (newselectedSubjects) => {
    setSelectedSubjects(newselectedSubjects);
    if (newselectedSubjects.length > 0) {
      setAreSubSelected(true);
    } else {
      setAreSubSelected(false);
    }
  };

  return (
    <div>
      {/* Main Page */}
      {currentPage === 1 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
             <p style={{fontWeight: 'bold', fontSize: '20px'}}>Kατάσταση: {infoList[state]}</p>
             {state === 0 && (
                <div style={{ flex: 1, textAlign: 'center' }}> 
                    {<p style={{ color: 'red', fontSize: '18px' }}>Δεν εχει πραγματοποιηθεί κάποια δηλωση για το τρέχον εξάμηνο</p>}
                    <p style={{fontSize: '18px' }}>Διορία: 20/02/2024</p>
                    <button className="green-button" onClick={() => handleNextPage('ΝΕΑ ΔΗΛΩΣΗ')}>ΝΕΑ ΔΗΛΩΣΗ</button>            
                </div>
            )}
             {state === 1 && (
                <div style={{ flex: 1, textAlign: 'center' }}> 
                  <div style={{ flex: 1, textAlign: 'center' }}>
                  <h2>Η δηλωσή σας</h2>
                  <table style={{ width: '100%' }}>
                    <thead>
                      <tr>
                        <th>Όνομα μαθήματος</th>
                        <th>ECTS</th>
                        <th>Κωδικός μαθήματος</th>
                        <th>Εξάμηνο</th>
                      </tr>
                    </thead>
                    <tbody>
                      {selectedSubjects.map((subject, index) => (
                        <tr key={index}>
                          <td>{subject.name}</td>
                          <td>{subject.ects}</td>
                          <td>{subject.code}</td>
                          <td>{subject.semester}</td>
                        </tr>
                      ))}
                    </tbody>
                  </table>
                </div>            
                    <button className="blue-button" onClick={() => handleEditPage('ΕΠΕΞΕΡΓΑΣΙΑ ΔΗΛΩΣΗΣ')}>ΕΠΕΞΕΡΓΑΣΙΑ ΔΗΛΩΣΗΣ</button>
                </div>
            )}
             {state === 2 && (
                <div>             
                  <div style={{ flex: 1, textAlign: 'center' }}>
                  <h2>Η δηλωσή σας</h2>
                  <table style={{ width: '100%' }}>
                    <thead>
                      <tr>
                        <th>Όνομα μαθήματος</th>
                        <th>ECTS</th>
                        <th>Κωδικός μαθήματος</th>
                        <th>Εξάμηνο</th>
                      </tr>
                    </thead>
                    <tbody>
                      {selectedSubjects.map((subject, index) => (
                        <tr key={index}>
                          <td>{subject.name}</td>
                          <td>{subject.ects}</td>
                          <td>{subject.code}</td>
                          <td>{subject.semester}</td>
                        </tr>
                      ))}
                    </tbody>
                  </table>
                </div>   
                </div>
            )}
             <br></br>
             <br></br>
             <br></br>
             <button className="blue-button" onClick={() => handleHistoryPage('ΙΣΤΟΡΙΚΟ')}>ΙΣΤΟΡΙΚΟ</button>
          </div>
      )}

      {/* NEA ΔΗΛΩΣΗ PAGE */}
      {currentPage === 2 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
             <p style = {{fontSize: '18px'}}>Υπάρχουν μαθήματα από προηγούμενες δηλώσεις που δεν εξετάστηκαν ή δεν εξετάστηκαν επιτυχώς.
             <br></br>Θα θέλατε να τα προσθέσετε στην τωρινή σας δήλωση;</p>
             <br></br>
             <ApplySubjectListWithCheckBox subjects={OldSubjects} onSubjectChange={handleSubjectChange} /> 
             <br></br>
             <br></br>
             <button className="simple-button" onClick={handleNextPage}>ΠΑΡΑΛΕΙΨΗ</button>
             <button className="simple-button" onClick={handleReturnClick}>ΠΡΟΗΓΟΥΜΕΝΟ</button>
             <button className="simple-button" onClick={handleClickedItems}>ΕΠΟΜΕΝΟ</button>
             
           </div>
      )} 

      {/* Select subjects */}
      {currentPage === 3 && (
        <div style={{ flex: 1, textAlign: 'center' }}>
          <ApplySemesterTree
            initialSubjects={selectedSubjects} 
            onSelectedSubjectsChange={handleSubjectChange} 
          />
          {!areSubSelected && errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
          <button className="simple-button" onClick={handlePreviousPage}>ΠΡΟΗΓΟΥΜΕΝΟ</button>
          <button className="simple-button" onClick={handleFinalApply}>ΟΡΙΣΤΙΚΟΠOΙΗΣΗ ΔΗΛΩΣΗΣ</button>
          <button className="save-button" onClick={handleSavedClick}>ΑΠΟΘΗΚΕΥΣΗ</button>
          <br></br>
          <p style = {{color: 'red'}}>ΠΡΟΣΟΧΗ! ΑΝ ΕΠΙΛΕΞΕΤΕ "ΟΡΙΣΤΙΚΟΠOΙΗΣΗ", ΔΕΝ ΘΑ ΜΠΟΡΕΙΤΕ ΝΑ ΕΠΕΞΕΡΓΑΣΤΕΙΤΕ ΣΤΗΝ ΣΥΝΕΧΕΙΑ ΤΗΝ ΔΗΛΩΣΗ ΣΑΣ</p>
        </div>
      )}

      {/* SAVED APPLY */}
      {currentPage === 4 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
            <div style={{ flex: 1, textAlign: 'center' }}>
              <h2>Η δήλωση σας</h2>
              <table style={{ width: '100%' }}>
                <thead>
                  <tr>
                    <th>Όνομα μαθήματος</th>
                    <th>ECTS</th>
                    <th>Κωδικός μαθήματος</th>
                    <th>Εξάμηνο</th>
                  </tr>
                </thead>
                <tbody>
                  {selectedSubjects.map((subject, index) => (
                    <tr key={index}>
                      <td>{subject.name}</td>
                      <td>{subject.ects}</td>
                      <td>{subject.code}</td>
                      <td>{subject.semester}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
            <br></br>
            <br></br>
            <p style={{ color: 'green', fontSize: '18px' }}>Η δηλωσή σας ολοκληρώθηκε με επιτυχία!</p>
            <button className="simple-button" onClick={handleReturnClick}>ΕΠΙΣΤΡΟΦΗ</button>
           </div>
      )}

      {/* ΟΡΙΣΤΙΚΟΠΟΙΗΜΕΝΗ ΔΗΛΩΣΗ */}
      {currentPage === 20 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
            <div style={{ flex: 1, textAlign: 'center' }}>
              <h2>Η δήλωση σας</h2>
              <table style={{ width: '100%' }}>
                <thead>
                  <tr>
                    <th>Όνομα μαθήματος</th>
                    <th>ECTS</th>
                    <th>Κωδικός μαθήματος</th>
                    <th>Εξάμηνο</th>
                  </tr>
                </thead>
                <tbody>
                  {selectedSubjects.map((subject, index) => (
                    <tr key={index}>
                      <td>{subject.name}</td>
                      <td>{subject.ects}</td>
                      <td>{subject.code}</td>
                      <td>{subject.semester}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
            <p style = {{color: 'green', fontSize: '18px'}}>Η δηλωσή σας οριστικοποιήθηκε με επιτυχία!</p>
            <button className="simple-button" onClick={handleReturnClick}>ΕΠΙΣΤΡΟΦΗ</button>
           </div>
      )}

      {/* EDIT PAGE */}
      {currentPage === 5 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
            <ApplySemesterTree
              initialSubjects={selectedSubjects}
              onSelectedSubjectsChange={handleSubjectChange}
            />
            {!areSubSelected && errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
             <button className="save-button" onClick={handleSavedClick}>ΑΠΟΘΗΚΕΥΣΗ</button>
             <button className="simple-button" onClick={handleFinalApply}>ΟΡΙΣΤΙΚΟΠOΙΗΣΗ ΔΗΛΩΣΗΣ</button>
             <button className="simple-button" onClick={handleReturnClick}>Προηγούμενο</button>
             <br></br>
            <p style={{ color: 'red' }}>ΠΡΟΣΟΧΗ! ΑΝ ΕΠΙΛΕΞΕΤΕ "ΟΡΙΣΤΙΚΟΠOΙΗΣΗ", ΔΕΝ ΘΑ ΜΠΟΡΕΙΤΕ ΝΑ ΕΠΕΞΕΡΓΑΣΤΕΙΤΕ ΣΤΗΝ ΣΥΝΕΧΕΙΑ ΤΗΝ ΔΗΛΩΣΗ ΣΑΣ</p>
           </div>
      )}

      {/* page of "ΙΣΤΟΡΙΚΟ" */}
      {currentPage === 10 && (
          <div style={{ flex: 1, textAlign: 'center' }}>
             <h1 style ={{color: 'black'}}>ΙΣΤΟΡΙΚΟ ΔΗΛΩΣΕΩΝ</h1>
             <p style={{fontSize: '18px', fontWeight: 'bold'}}>ΕΑΡΙΝΗ ΔΗΛΩΣΗ: 17/4/2021</p>  
                ΜΑΘΗΜΑ 1<br></br> 
                ΜΑΘΗΜΑ 2<br></br>
                ΜΑΘΗΜΑ 3
              <p style={{ fontSize: '18px', fontWeight: 'bold' }}>ΧΕΙΜΕΡΙΝΗ ΔΗΛΩΣΗ: 17/12/2022</p>
                ΜΑΘΗΜΑ 4<br></br> 
                ΜΑΘΗΜΑ 5<br></br>
                ΜΑΘΗΜΑ 6
              <p style={{ fontSize: '18px', fontWeight: 'bold' }}>ΕΑΡΙΝΗ ΔΗΛΩΣΗ: 17/12/2022</p>
                ΜΑΘΗΜΑ 7<br></br> 
                ΜΑΘΗΜΑ 8<br></br>
                ΜΑΘΗΜΑ 9
             <br></br>   
             <br></br>  
             <button className="simple-button" onClick={handleReturnClick}>Προηγούμενο</button>
           </div>
         )} 
    </div>
  );
};

export default InfoPage;
