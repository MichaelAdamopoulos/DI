import React, { useState } from 'react';

const Dropdown = () => {
  const [selectedOption, setSelectedOption] = useState('');

  const handleDropdownChange = (event) => {
    setSelectedOption(event.target.value);
  };

  return (
    <div>
      <label htmlFor="dropdown">Επιλέξτε το πιστοποιητικό που επιθυμείτε :  </label>
      <select id="dropdown" value={selectedOption} onChange={handleDropdownChange}>
        <option value="Φοιτητικη Ιδιοτητα">Φοιτητικής Ιδιότητα</option>
        <option value="Φορολογικης Χρησης">Φορολογικής Χρήσης</option>
        <option value="Στρατολογικη Χρηση">Στρατολογικής Χρήσης</option>
      </select>
    </div>
  );
};

export default Dropdown;
