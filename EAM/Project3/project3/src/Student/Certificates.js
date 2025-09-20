import React, { useState } from 'react';
import NavBar from "./NavBar"
import Dropdown from './Cert_Dropdown';
import NumberDropdown from './Cert_NumberDropdown';
import HelpBar from "./HelpBar"
import './AppButtonStyles.css';

export default function Certificates() {
    const [selectedOption, setSelectedOption] = useState(null);
    const [showDetails, setShowDetails] = useState(false);
    const [currentPage, setCurrentPage] = useState(1);
  
    const handleOptionClick = (option) => {
      setSelectedOption(option);
    };
  
    const handleNextClick = () => {
      if (selectedOption) {
        if (selectedOption  === 'ΙΣΤΟΡΙΚΟ') {
          setCurrentPage(6);
        }
        else {
          setShowDetails(true);
          setCurrentPage(currentPage + 1);
        }
      }
    };
  
    const handlePreviousClick = () => {
      if (selectedOption  === 'ΙΣΤΟΡΙΚΟ') {
        setCurrentPage(1);
      }
      else {
        if (currentPage === 5)
          setCurrentPage(1);
        else {
          setCurrentPage(currentPage - 1);
        }
      }
    };
  
    const handleNextPageClick = () => {
      setCurrentPage(currentPage + 1);
    };
  
    const handleCancelClick = () => {
      setSelectedOption(null);
      setShowDetails(false);
      setCurrentPage(1);
    };

    return (
      <div style={{ flex: 1, textAlign: 'center' }}>
        <NavBar/>
        {/* main page of Certificates */}
        {currentPage === 1 && (
          <div style = {{fontSize: '20px'}}>
            <p style={{color: 'blue', fontWeight: 'bold', fontSize: '25px'}}>ΕΠΙΛΕΞΤΕ ΜΙΑ ΕΝΕΡΓΕΙΑ</p>
            <div>
            <br></br>
              <div
                style={{
                  width: '20px',
                  height: '20px',
                  borderRadius: '50%',
                  backgroundColor: selectedOption === 'ΝΕΑ ΑΙΤΗΣΗ' ? 'blue' : 'lightgray',
                  display: 'inline-block',
                  cursor: 'pointer',
                  marginRight: '10px',
                  verticalAlign: 'middle',
                }}
                onClick={() => handleOptionClick('ΝΕΑ ΑΙΤΗΣΗ')}
              >
              </div>   
              ΝΕΑ ΑΙΤΗΣΗ           
              <br></br>
              <br></br>
              <br></br>
              <br></br>
              <div
                style={{
                  width: '20px',
                  height: '20px',
                  borderRadius: '50%',
                  backgroundColor: selectedOption === 'ΙΣΤΟΡΙΚΟ' ? 'blue' : 'lightgray',
                  display: 'inline-block',
                  cursor: 'pointer',
                  marginRight: '20px',
                  verticalAlign: 'middle'
                }}
                onClick={() => handleOptionClick('ΙΣΤΟΡΙΚΟ')}
              ></div>
              ΙΣΤΟΡΙΚΟ
            </div>
              <br></br>
              <br></br>
              <br></br>
            <button className="simple-button" onClick={handleNextClick}>Επόμενο</button>
          </div>
        )}
        {/* ΑΥΤΟΜΑΤΗ ΣΥΜΠΛΗΡΩΣΗ */}
        {currentPage === 2 && showDetails && (
          <div>
            <p style = {{fontWeight: 'bold', color: 'blue', fontSize: '20px'}}>ΑΥΤΟΜΑΤΗ ΣΥΜΠΛΗΡΩΣΗ 1/3</p>
            <br></br>
            <p><strong>Όνομα:</strong>Μιχάλης</p>
            <p><strong>Επώνυμο:</strong>Γκιούζι</p>
            <p><strong>Πόλη:</strong>Αθήνα</p>
            <p><strong>Αριθμός Μητρώου:</strong>1234567890</p>
            <p><strong>Αριθμός Τηλεφώνου:</strong>1234567890</p>
            <br></br>
            <button className="simple-button" onClick={handlePreviousClick}>Προηγούμενο</button>
            <button className="simple-button" onClick={handleNextPageClick}>Επόμενο</button>
            <br></br>
            <button className="red-button" onClick={handleCancelClick}>Ακύρωση</button>
          </div>
        )}
        {/* ΕΠΙΛΟΓΗ ΠΙΣΤΟΠΟΙΗΤΙΚΟΥ */}
        {currentPage === 3 && (
          <div>
            <p style={{ fontWeight: 'bold', color: 'blue', fontSize: '20px' }}>ΕΠΙΛΟΓΗ ΠΙΣΤΟΠΟΙΗΤΙΚΟΥ 2/3</p>
            <br></br>
            <Dropdown/>
            <br></br>
            <button className="simple-button" onClick={handlePreviousClick}>Προηγούμενο</button>
            <button className="simple-button" onClick={handleNextPageClick}>Επόμενο</button>
            <br></br>
            <button className="red-button" onClick={handleCancelClick}>Ακύρωση</button>
          </div>
        )}
        {/* ΕΠΙΛΟΓΗ ΑΝΤΙΤΥΠΩΝ */}
        {currentPage === 4 && (
          <div>
            <p style={{ fontWeight: 'bold', color: 'blue', fontSize: '20px' }}> ΕΠΙΛΟΓΗ ΑΝΤΙΤΥΠΩΝ 3/3</p>
            <br></br>
            <NumberDropdown/>
            <br></br>
            <button className="simple-button" onClick={handlePreviousClick}>Προηγούμενο</button>
            <button className="green-button" onClick={handleNextPageClick}>Ολοκληρωση Αιτησης</button>
            <br></br>
            <button className="red-button" onClick={handleCancelClick}>Ακύρωση</button>
          </div>
        )}
        {/* ΟΛΟΚΛΗΡΩΣΗ ΑΙΤΗΣΗΣ */}
        {currentPage === 5 && (
          <div>
            <h2>ΟΛΟΚΛΗΡΩΣΗ ΑΙΤΗΣΗΣ</h2>
            <p style={{ fontWeight: 'bold', color: 'green', fontSize: '20px' }}>Η αίτηση ολοκληρώθηκε με επιτυχία!</p>
            <br></br>
            <button className="simple-button" onClick={handlePreviousClick}>Επιστροφή</button>
          </div>
        )}
        {/* "ΙΣΤΟΡΙΚΟ" */}
        {currentPage === 6 && (
          <div>
            <h2 style={{ color: 'blue' }}>ΙΣΤΟΡΙΚΟ ΠΙΣΤΟΠΟΙΗΤΙΚΩN</h2>
            <p><strong>ΦΟΙΤΗΤΙΚΗΣ ΙΔΙΟΤΗΤΑΣ:</strong> 04/10/2022</p>
            <p><strong>ΦΟΙΤΗΤΙΚΗΣ ΙΔΙΟΤΗΤΑΣ:</strong>17/12/2023</p>  
            <br></br>          
            <button className="simple-button" onClick={handlePreviousClick}>Προηγούμενο</button>
          </div>
        )}
        <HelpBar />
      </div>
    );
};
  
  
