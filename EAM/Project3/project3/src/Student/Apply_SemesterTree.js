import React, { useState, useEffect } from 'react';
import './AppButtonStyles.css';

const subjectsData = [
  {
    name: 'Εξάμηνο 1',
    subjects: [
      { name: 'Διακριτά', ects: 5, code: 'ΔΙΑ101', semester: 'Εξάμηνο 1' },
      { name: 'Λογική Σχεδίαση', ects: 6, code: 'ΛΟΓ102', semester: 'Εξάμηνο 1'  },
      { name: 'Εισαγωγή στον Προγραμματισμό', ects: 4, code: 'ΕΙΣ103', semester: 'Εξάμηνο 1'  },
      { name: 'Εισαγωγή στην Πληροφορική', ects: 7, code: 'ΕΙΣ104', semester: 'Εξάμηνο 1'  },
    ],
  },
  {
    name: 'Εξάμηνο 2',
    subjects: [
      { name: 'Ανάλυση 1', ects: 6, code: 'ΑΝΑ201', semester: 'Εξάμηνο 2' },
      { name: 'Δομές Δεδομένων', ects: 5, code: 'ΔΟΜ202', semester: 'Εξάμηνο 2' },
      { name: 'Αρχιτεκτονική Υπολογιστών', ects: 7, code: 'ΑΡΧ203', semester: 'Εξάμηνο 2' },
      { name: 'Φυσική', ects: 6, code: 'ΦΥΣ204', semester: 'Εξάμηνο 2' },
    ],
  },
  {
    name: 'Εξάμηνο 3',
    subjects: [
      { name: 'Πιθανότητες', ects: 5, code: 'ΠΙΘ301', semester: 'Εξάμηνο 3' },
      { name: 'Ανάλυση 2', ects: 7, code: 'ΑΝΑ302', semester: 'Εξάμηνο 3' },
      { name: 'Αντικειμενοστραφής Προγραμματισμός', ects: 6, code: 'ΑΝΤ303', semester: 'Εξάμηνο 3' },
      { name: 'Σήματα', ects: 6, code: 'ΣΗΜ304', semester: 'Εξάμηνο 3' },
    ],
  },
  {
    name: 'Εξάμηνο 4',
    subjects: [
      { name: 'Αλγόριθμοι', ects: 6, code: 'ΑΛΓ401', semester: 'Εξάμηνο 4' },
      { name: 'Σχεδίαση', ects: 7, code: 'ΣΧΕ402', semester: 'Εξάμηνο 4' },
      { name: 'Συστήματα Επικοινωνιών', ects: 6, code: 'ΣΥΣ403', semester: 'Εξάμηνο 4' },
      { name: 'Δίκτυα Επικοινωνιών', ects: 7, code: 'ΔΙΚ404', semester: 'Εξάμηνο 4' },
    ],
  },
  {
    name: 'Εξάμηνο 5',
    subjects: [
      { name: 'Λειτουργικά', ects: 7, code: 'ΛΕΙ501', semester: 'Εξάμηνο 5' },
      { name: 'Αρανάλ', ects: 5, code: 'ΑΡΑ502', semester: 'Εξάμηνο 5' },
      { name: 'ΥΣΒΔ', ects: 6, code: 'ΥΣΒΔ503', semester: 'Εξάμηνο 5' },
      { name: 'ΑΙ 1', ects: 8, code: 'ΑΙ504', semester: 'Εξάμηνο 5' },
    ],
  },
  {
    name: 'Εξάμηνο 6',
    subjects: [
      { name: 'Εξόρυξη Δεδομένων', ects: 6, code: 'ΕΞΟ601', semester: 'Εξάμηνο 6' },
      { name: 'Μαθηματικά Πληροφορικής', ects: 5, code: 'ΜΑΘ602', semester: 'Εξάμηνο 6' },
      { name: 'Προγραμματισμός Συστήματος', ects: 7, code: 'ΠΡΟΓ603', semester: 'Εξάμηνο 6' },
    ],
  },
  {
    name: 'Εξάμηνο 7',
    subjects: [
      { name: 'ΑΙ 2', ects: 7, code: 'ΑΙ701', semester: 'Εξάμηνο 7' },
      { name: 'ΕΑΜ', ects: 6, code: 'ΕΑΜ702', semester: 'Εξάμηνο 7' },
    ],
  },
  {
    name: 'Εξάμηνο 8',
    subjects: [
      { name: 'Project', ects: 8, code: 'ΠΡΟΙ801', semester: 'Εξάμηνο 8' },
    ],
  },
];

const ApplySemesterTree = ({ initialSubjects, onSelectedSubjectsChange }) => {
  const [selectedSemesters, setSelectedSemesters] = useState([]);
  const [selectedSubjects, setSelectedSubjects] = useState(
    initialSubjects.map((subject, index) => ({ ...subject, id: index }))
  );
  const [searchQuery, setSearchQuery] = useState('');
  const [filteredSubjects, setFilteredSubjects] = useState([]);
  const SUBJECT_LIMIT = 10;
  const [errorMessage, setErrorMessage] = useState('');

  useEffect(() => {
    if (initialSubjects && initialSubjects.length > 0) {
      const flattenedSubjects = initialSubjects.reduce(
        (accumulator, semester) => accumulator.concat(semester.subjects),
        []
      );

      const subjectsToAdd = flattenedSubjects.filter(
        (initialSubject) =>
          !selectedSubjects.find((subject) => subject.code === initialSubject?.code)
      );

      setSelectedSubjects((prevSelectedSubjects) =>
        prevSelectedSubjects.concat(
          subjectsToAdd
            .filter(subject => subject && subject.ects && subject.ects >= 4 && subject.ects <= 8)
            .map((subject) => ({
              ...subject,
              id: prevSelectedSubjects.length,
            }))
        )
      );
    }
  }, [initialSubjects, selectedSubjects.length, selectedSubjects]);

  useEffect(() => {
    onSelectedSubjectsChange(selectedSubjects);
  }, [onSelectedSubjectsChange, selectedSubjects]);

  const handleSemesterClick = (semester) => {
    setSelectedSemesters((prevSelectedSemesters) => {
      if (prevSelectedSemesters.includes(semester)) {
        return prevSelectedSemesters.filter((selectedSem) => selectedSem !== semester);
      } else {
        return [...prevSelectedSemesters, semester];
      }
    });

    setSearchQuery('');
    setFilteredSubjects([]);
    setErrorMessage('');
  };

  const handleSubjectClick = (subject) => {
    if (selectedSubjects.length < SUBJECT_LIMIT) {
      if (!selectedSubjects.find((selectedSubject) => selectedSubject.code === subject.code)) {
        setSelectedSubjects((prevSelectedSubjects) =>
          prevSelectedSubjects.concat({ ...subject, id: prevSelectedSubjects.length })
        );
        setErrorMessage('');
      }
    } else {
      setErrorMessage(`Το όριο των μαθημάτων για το εξάμηνο είναι ${SUBJECT_LIMIT}.`);
    }
  };

  const handleRemoveSubject = (subjectToRemove) => {
    setSelectedSubjects((prevSelectedSubjects) =>
      prevSelectedSubjects.filter((subject) => subject.id !== subjectToRemove.id)
    );
  };

  const handleSearchSubjectSelect = (subject) => {
    if (selectedSubjects.length < SUBJECT_LIMIT) {
      if (!selectedSubjects.find((selectedSubject) => selectedSubject.code === subject.code)) {
        setSelectedSubjects((prevSelectedSubjects) => [
          ...prevSelectedSubjects,
          { ...subject, id: prevSelectedSubjects.length },
        ]);
        setSearchQuery('');
        setFilteredSubjects([]);
        setErrorMessage('');
      }
    } else {
      setErrorMessage(
        `Το όριο των μαθημάτων για το εξάμηνο είναι ${SUBJECT_LIMIT}.`
      );
    }
  };

  const handleSearchInputChange = (event) => {
    const query = event.target.value.toLowerCase();
    setSearchQuery(query);

    if (query === '') {
      setFilteredSubjects([]);
    } else {
      const filtered = subjectsData
        .flatMap((semester) => semester.subjects)
        .filter((subject) => subject.name.toLowerCase().includes(query));

      setFilteredSubjects(filtered);
    }
  };

  return (
    <div style={{ display: 'flex', height: '70vh', overflow: 'hidden' }}>
      <div style={{ marginRight: '20px', maxHeight: '70vh', overflowY: 'auto' }}>
        <input
          type="text"
          placeholder="Αναζήτηση Μαθήματος..."
          value={searchQuery}
          onChange={handleSearchInputChange}
        />
        <ul style={{ listStyle: 'none' }}>
          {filteredSubjects.map((subject, index) => (
            <li
              key={index}
              onClick={() => handleSearchSubjectSelect(subject)}
              style={{ cursor: 'pointer' }}
            >
              {subject.name}
            </li>
          ))}
        </ul>

        {subjectsData.map((semester, index) => (
          <div key={index}>
            <h3
              onClick={() => handleSemesterClick(semester)}
              style={{
                cursor: 'pointer',
                color: selectedSemesters.includes(semester) ? 'blue' : 'black',
              }}
            >
              {semester.name}
            </h3>
            {selectedSemesters.includes(semester) && (
              <ul>
                {semester.subjects.map((subject, subjectIndex) => (
                  <li key={subjectIndex} style={{ display: 'flex', alignItems: 'center' }}>
                    <div
                      onClick={() => handleSubjectClick(subject)}
                      style={{ cursor: 'pointer', marginRight: '5px' }}
                    >
                      {subject.name}
                    </div>
                  </li>
                ))}
              </ul>
            )}
          </div>
        ))}
      </div>

      {/* ΕΠΙΛΕΓΜΕΝΑ ΜΑΘΗΜΑΤΑ */}
      <div style={{ flex: 1, textAlign: 'center', overflow: 'auto' }}>
        <h2>ΕΠΙΛΕΓΜΕΝΑ ΜΑΘΗΜΑΤΑ</h2>
        {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
        <table style={{ width: '100%' }}>
          <thead>
            <tr>
              <th>Όνομα</th>
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
                <td>
                  <button className="red-button" onClick={() => handleRemoveSubject(subject)}>
                    x
                  </button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );
};

export default ApplySemesterTree;