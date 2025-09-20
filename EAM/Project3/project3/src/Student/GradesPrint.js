import React from 'react';
import { useLocation } from 'react-router-dom';
import { Link } from 'react-router-dom';
import './GradesPrint.css'

const PrintGrades = () => {
    const location = useLocation();
    const { state } = location;

    console.log(state.hi)
    const filteredExams = state.hi;

    return (
        <div className="Semesters">
            <h1>ΒΑΘΜΟΛΟΓΙΑ</h1>
            {filteredExams.map((exam, index) => (
                <div key={index} style={{ marginBottom: '15px' }}>
                    <div className='Labels'>
                        {exam.period} {exam.year}
                    </div>
                    <ul>
                        {exam.subjects.map((subject, subIndex) => (
                            <li
                                key={subIndex}
                                style={{ color: subject.grade >= 5 ? 'green' : 'red' }}
                            >
                                {subject.name}: {subject.grade}
                            </li>
                        ))}
                    </ul>
                </div>
            ))}
            {/*This button does nothing*/}
            <button className="OkButton">OK</button>
            <Link className = "CancelLink" to = '/student/grades'>
                Cancel
            </Link>
        </div>
        
    );
};

export default PrintGrades;

