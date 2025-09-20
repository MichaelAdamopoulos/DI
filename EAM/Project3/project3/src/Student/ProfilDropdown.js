import React, { useState } from 'react';
import './ProfilDropdown.css'

export default function ProfilDropdown({ about, personal, contact }) {
  const [isOpen, setIsOpen] = useState([true, true, true]);
  const [isEditMode, setIsEditMode] = useState(false);
  const [editedAbout, setEditedAbout] = useState(about);
  const [editedPersonal, setEditedPersonal] = useState(personal);
  const [editedContact, setEditedContact] = useState(contact);
  const [oldAbout, setOldAbout] = useState(null);
  const [oldPersonal, setOldPersonal] = useState(null);
  const [oldContact, setOldContact] = useState(null);

  const toggleDropdown = (index) => {
    setIsOpen((prevIsOpen) => {
      const newIsOpen = [...prevIsOpen];
      newIsOpen[index] = !newIsOpen[index];
      return newIsOpen;
    });
  };

  const handleEditClick = () => {
    setIsEditMode(!isEditMode);
    !isEditMode && setIsOpen([true, true, true]);

    if (!isEditMode) {
      setOldAbout([...editedAbout]);
      setOldPersonal([...editedPersonal]);
      setOldContact([...editedContact]);
    }
  };

  const handleCancelClick = () => {
    setEditedAbout([...oldAbout]);
    setEditedPersonal([...oldPersonal]);
    setEditedContact([...oldContact]);
    setIsEditMode(false);
  };

  const handleInputChange = (category, itemId, value) => {
    switch (category) {
      case 'about':
        setEditedAbout((prevAbout) =>
          prevAbout.map((item) => (item.id === itemId ? { ...item, info: value } : item))
        );
        break;
      case 'personal':
        setEditedPersonal((prevPersonal) =>
          prevPersonal.map((item) => (item.id === itemId ? { ...item, info: value } : item))
        );
        break;
      case 'contact':
        setEditedContact((prevContact) =>
          prevContact.map((item) => (item.id === itemId ? { ...item, info: value } : item))
        );
        break;
      default:
        break;
    }
  };

  return (
    <div className="ProfilDropdown">  
      <div className="Headers" onClick={() => toggleDropdown(0)}>
        ΣΧΕΤΙΚΑ ME ΤΙΣ ΣΠΟΥΔΕΣ MOY
      </div>
      {isOpen[0] && (
        <dl>
          {editedAbout.map((item) => (
            <dd key={item.id}>
              <span className="title">{item.title}</span>{' '}
              {item.edit === 'true' && isEditMode ? (
                <input
                  type="text"
                  value={item.info}
                  onChange={(e) => handleInputChange('about', item.id, e.target.value)}
                />
              ) : (
                <span className="info">{item.info}</span>
              )}
            </dd>
          ))}
        </dl>
      )}

      <div className="Headers" onClick={() => toggleDropdown(1)}>
        ΠΡΟΣΩΠΙΚΑ ΣΤΟΙΧΕΙΑ
      </div>
      {isOpen[1] && (
        <dl>
          {editedPersonal.map((item) => (
            <dd key={item.id}>
              <span className="title">{item.title}</span>{' '}
              {item.edit === 'true' && isEditMode ? (
                <input
                  type="text"
                  value={item.info}
                  onChange={(e) => handleInputChange('personal', item.id, e.target.value)}
                />
              ) : (
                <span className="info">{item.info}</span>
              )}
            </dd>
          ))}
        </dl>
      )}

      <div className="Headers" onClick={() => toggleDropdown(2)}>
        ΣΤΟΙΧΕΙΑ ΕΠΙΚΟΙΝΩΝΙΑΣ
      </div>
      {isOpen[2] && (
        <dl>
          {editedContact.map((item) => (
            <dd key={item.id}>
              <span className="title">{item.title}</span>{' '}
              {item.edit === 'true' && isEditMode ? (
                <input
                  type="text"
                  value={item.info}
                  onChange={(e) => handleInputChange('contact', item.id, e.target.value)}
                />
              ) : (
                <span className="info">{item.info}</span>
              )}
            </dd>
          ))}
        </dl>
      )}
      <button className="SaveEdit" onClick={handleEditClick}>
        {isEditMode ? 'ΑΠΟΘΗΚΕΥΣΗ' : 'ΕΠΕΞΕΡΓΑΣΙΑ'}
      </button>
      {isEditMode && <button className="Cancel" onClick={handleCancelClick}> ΑΚΥΡΩΣΗ </button>}
    </div>
  );
}
