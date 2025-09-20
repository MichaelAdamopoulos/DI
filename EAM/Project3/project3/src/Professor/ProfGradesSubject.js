import React, { useState, useEffect } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import './ProfGradesSubject.css';

const ProfGradesSubject = () => {
    const location = useLocation();
    const navigate = useNavigate();
    const { state } = location;
    const selectedSubject = state?.subject;

    const [isEditing, setIsEditing] = useState(false);
    const [editedStudents, setEditedStudents] = useState([]);

    useEffect(() => {
        setEditedStudents(selectedSubject?.students || []);
    }, [selectedSubject]);

    if (!selectedSubject) {
        return <div>Δεν επιλέχθηκε κάποιο μάθημα</div>;
    }

    const studentLabels = ['name', 'code', 'semester', 'period', 'grade', 'exclusion'];
    const backupLabels = ['Όνομα', 'Κωδικός', 'Εξάμηνο', 'Περίοδος', 'Βαθμός', 'Απαλλαγή'];

    const handleEditClick = () => {
        setEditedStudents([...selectedSubject.students]);
        setIsEditing(true);
    };

    const handleSaveClick = () => {
        setIsEditing(false);
    };

    const handleGradeChange = (index, value) => {
        const updatedStudents = [...editedStudents];
        updatedStudents[index].grade = value;
        setEditedStudents(updatedStudents);
    };

    const handleReturnClick = () => {
        navigate(-1);
    };

    return (
        <div className="subject-details-container">
            <h2>{selectedSubject.ΟΝΟΜΑ}</h2>
            <div className="subject-details">
                <strong>ΤΜΗΜΑ: {selectedSubject.ΤΜΗΜΑ} </strong>
                <br />
                <br />
                <strong>ΚΩΔΙΚΟΣ: {selectedSubject.ΚΩΔΙΚΟΣ}</strong>
            </div>
            <br />
            <h3>ΦΟΙΤΗΤΕΣ</h3>
            <ul className="student-label">
                {backupLabels.map((label, labelIndex) => (
                    <li key={labelIndex}>{label}</li>
                ))}
            </ul>
            <ul className="student-details">
                {editedStudents.map((student, studentIndex) => (
                    <li key={studentIndex} className="student">
                        {studentLabels.map((label, labelIndex) => (
                            <div key={labelIndex} className="label-value">
                                {isEditing ? (
                                    label === 'grade' ? (
                                        <input
                                            type="text"
                                            value={student.grade}
                                            onChange={(e) => handleGradeChange(studentIndex, e.target.value)}
                                        />
                                    ) : (
                                        student[label.toLowerCase()]
                                    )
                                ) : (
                                    student[label.toLowerCase()]
                                )}
                            </div>
                        ))}
                    </li>
                ))}
            </ul>
            <div style={{ textAlign: 'center' }}>
                <button className="simple-button" onClick={handleReturnClick}>ΕΠΙΣΤΡΟΦΗ</button>
                {isEditing && selectedSubject.ΒΑΘΜΟΙ !== 'Εμφάνιση' && (
                    <button className="green-button" onClick={handleSaveClick}>ΑΠΟΘΗΚΕΥΣΗ</button>
                )}
                {!isEditing && selectedSubject.ΒΑΘΜΟΙ !== 'Εμφάνιση' && (
                    <>
                        <button className="simple-button" onClick={handleEditClick}>ΕΠΕΞΕΡΓΑΣΙΑ</button> 
                    </>
                )}
            </div>
        </div>
    );
};

export default ProfGradesSubject;

