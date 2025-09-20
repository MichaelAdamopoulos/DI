import React, { useState } from 'react';

const NumberDropdown = () => {
    const [selectedOption, setSelectedOption] = useState('');
  
    const handleDropdownChange = (event) => {
      setSelectedOption(event.target.value);
    };
  
    return (
      <div>
        <label htmlFor="NumberDropdown">Επιλεξτε τον αριθμο των αντιτύπων που επιθυμειτε:  </label>
        <select id="NumberDropdown" value={selectedOption} onChange={handleDropdownChange}>
          <option value="1">1</option>
          <option value="2">2</option>
          <option value="3">3</option>
        </select>
      </div>
    );
  };

export default NumberDropdown