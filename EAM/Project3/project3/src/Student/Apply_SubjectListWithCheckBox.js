import React, { useState, useEffect } from 'react';

const ApplySubjectListWithCheckBox = ({ subjects, onSubjectChange }) => {
  const [selectedSubjects, setSelectedSubjects] = useState([]);

  useEffect(() => {
    onSubjectChange(selectedSubjects);
  }, [selectedSubjects, onSubjectChange]);

  const handleCheckBoxClick = (subject) => {
    if (selectedSubjects.some((selectedSubject) => selectedSubject.code === subject.code)) {
      setSelectedSubjects((prevSelectedSubjects) =>
        prevSelectedSubjects.filter((item) => item.code !== subject.code)
      );
    } else {
      setSelectedSubjects((prevSelectedSubjects) => [...prevSelectedSubjects, subject]);
    }
  };

  return (
    <div>
      <ul style={{listStyle: 'none', fontSize: "18px"}}>
        {subjects.map((subject, index) => (
          <li key={index}>
            <div>
              <span>{subject.name}</span>
              <input
                type="checkbox"
                checked={selectedSubjects.some((selectedSubject) => selectedSubject.code === subject.code)}
                onChange={() => handleCheckBoxClick(subject)}
              />
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default ApplySubjectListWithCheckBox;

