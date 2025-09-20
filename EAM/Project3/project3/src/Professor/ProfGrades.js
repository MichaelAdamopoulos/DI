import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import './ProfGrades.css';
import ProfHelpBar from './ProfHelpBar'
import ProfNavBar from './ProfNavBar'

const ProfGrades = () => {
    const [subjects, setSubjects] = useState([
        {
            ΟΝΟΜΑ: 'Αναλυση 1',
            ΤΜΗΜΑ: 'Μαθηματικό',
            ΚΩΔΙΚΟΣ: 'ΜΑ101',
            ΦΟΙΤΗΤΕΣ: 50,
            ΕΝΕΡΓΟ: 'Ενεργό',
            ΒΑΘΜΟΙ: 'Εμφάνιση',
            students: [
                { name: 'Μιχάλης', code: 'S123', semester: 4, period: 'ΕΑΡΙΝΟ', grade: '5', exclusion: 'OXI' },
                { name: 'Οργκές', code: 'Κ234', semester: 4, period: 'ΕΑΡΙΝΟ', grade: '6', exclusion: 'NAI' },
                { name: 'Γιώργος', code: 'S193', semester: 4, period: 'ΕΑΡΙΝΟ', grade: '7', exclusion: 'OXI' },
                { name: 'Μαρία', code: 'Κ279', semester: 8, period: 'ΕΑΡΙΝΟ', grade: '8', exclusion: 'OXI' },
            ],
        },
        {
            ΟΝΟΜΑ: 'Αρχιτεκτονική 1',
            ΤΜΗΜΑ: 'Πληροφορικής',
            ΚΩΔΙΚΟΣ: 'ΑΡΧM303',
            ΑΡΙΘΜΟΣ_ΦΟΙΤΗΤΩΝ: 40,
            ΕΝΕΡΓΟ: 'Ενεργό',
            ΒΑΘΜΟΙ: 'Επεξεργασία',
            students: [
                { name: 'Γιάννης', code: 'S456', semester: 2, period: 'ΧΕΙΜΕΡΙΝΟ', grade: '1', exclusion: 'OXI' },
                { name: 'Κατερίνα', code: 'S457', semester: 3, period: 'ΧΕΙΜΕΡΙΝΟ', grade: '2', exclusion: 'OXI' },
                { name: 'Ελένη', code: 'S163', semester: 6, period: 'ΧΕΙΜΕΡΙΝΟ', grade: '5', exclusion: 'OXI' },
            ],
        },
    ]);

    const [sortConfig, setSortConfig] = useState({
        key: null,
        order: 'asc',
    });

    const labels = Object.keys(subjects[0]).filter((key) => key !== 'students');

    const handleSort = (label) => {
        let order = 'asc';
        if (sortConfig.key === label && sortConfig.order === 'asc') {
            order = 'desc';
        }

        setSortConfig({ key: label, order });

        const sortedSubjects = [...subjects].sort((a, b) => {
            const aValue = a[label];
            const bValue = b[label];

            if (typeof aValue === 'string' && typeof bValue === 'string') {
                return order === 'asc' ? aValue.localeCompare(bValue) : bValue.localeCompare(aValue);
            } else {
                return order === 'asc' ? aValue - bValue : bValue - aValue;
            }
        });

        setSubjects(sortedSubjects);
    };

    return (
        <div>
            <ProfNavBar />
            <div className="prof-grades-container">
                <div className="labels-container">
                    {labels.map((label) => (
                        <div
                            key={label}
                            className="label"
                            onClick={() => handleSort(label)}
                            style={{ cursor: 'pointer' }}
                        >
                            {label}
                        </div>
                    ))}
                </div>
                {subjects.map((subject, index) => (
                    <div key={index} className="subject-container">
                        {Object.entries(subject)
                            .filter(([key]) => key !== 'students')
                            .map(([key, value], valueIndex) => (
                                <div key={valueIndex} className="value">
                                    {key === 'ΟΝΟΜΑ' ? (
                                        <Link
                                            to={`/professor/grades/${value}`}
                                            state={{ subject: { ...subject } }}
                                        >
                                            {value}
                                        </Link>
                                    ) : String(value)}
                                </div>
                            ))}
                    </div>
                ))}
            </div>
            <ProfHelpBar />
        </div>
    );
};

export default ProfGrades;