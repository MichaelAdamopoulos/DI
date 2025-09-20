import './ProfSubjects.css'
import React, { useState } from 'react';
import ProfNavBar from './ProfNavBar'
import ProfHelpBar from './ProfHelpBar'

export default function ProfSubjects() {
    const [subjects, setSubjects] = useState([
        {
            name: 'Αναλυση 1',
            department: 'Μαθηματικό',
            code: 'ΜΑ101',
            activeness: 'Ενεργό',
            period: '1ο Εξάμηνο',
            time: '9:00 ΠΜ - 10:30 ΠΜ',
            extraDetails: [
                { label: 'Ακαδημαικό Έτος', value: '1ο' },
                { label: 'Τίτλος', value: 'Ανάλυση 1' },
                { label: 'Συντομογραφία', value: 'Ανα 1' },
                { label: 'Περιγραφή', value: 'Εκμάθηση Σύνθετων Ολοκληρωμάτων και της χρησιμοποίησης τους' },
            ],
            isOpen: false,
        },
        {
            name: 'Γραμμική Άλγεβρα',
            department: 'Πληροφορικής',
            code: 'ΓΡΑ202',
            activeness: 'Ανενεργό',
            period: '2ο Εξάμηνο',
            time: '2:00 ΜΜ - 3:30 ΜΜ',
            extraDetails: [
                { label: 'Ακαδημαικό Έτος', value: '1ο' },
                { label: 'Τίτλος', value: 'Γραμμική Άλγεβρα' },
                { label: 'Συντομογραφία', value: 'ΓραΑλ' },
                { label: 'Περιγραφή', value: 'Εισαγωγή στους Πίνακες' },
            ],
            isOpen: false,
        },
        {
            name: 'Αρχιτεκτονική 1',
            department: 'Πληροφορικής',
            code: 'ΑΡΧM303',
            activeness: 'Ενεργό',
            period: '3ο Εξάμηνο',
            time: '11:00 ΠΜ - 12:30 ΜΜ',
            extraDetails: [
                { label: 'Ακαδημαικό Έτος', value: '2ο' },
                { label: 'Τίτλος', value: 'Αρχιτεκτονική 1' },
                { label: 'Συντομογραφία', value: 'Αρχ 1' },
                { label: 'Περιγραφή', value: 'Ανάλυση ενδελεχώς των μερών του υπολογιστή' },
            ],
            isOpen: false,
        },
    ]);


    const [sortConfig, setSortConfig] = useState({ key: null, direction: 'asc' });

    const sortSubjects = (key) => {
        let direction = 'asc';
        if (sortConfig.key === key && sortConfig.direction === 'asc') {
            direction = 'desc';
        }
        setSortConfig({ key, direction });
        setSubjects((prevSubjects) =>
            [...prevSubjects].sort((a, b) => {
                const aValue = a[key];
                const bValue = b[key];
                const comparison = aValue.localeCompare(bValue);
                return direction === 'asc' ? comparison : -comparison;
            })
        );
    };

    const toggleDetails = (index) => {
        setSubjects((prevSubjects) => {
            const newSubjects = [...prevSubjects];
            newSubjects[index] = { ...newSubjects[index], isOpen: !newSubjects[index].isOpen };
            return newSubjects;
        });
    };

    return (
        <div>
            <ProfNavBar/>
            <div className="subject-details">
                <div className="labels">
                    <div className="label" onClick={() => sortSubjects('name')}>
                        ΟΝΟΜΑ
                    </div>
                    <div className="label" onClick={() => sortSubjects('department')}>
                        ΤΜΗΜΑ
                    </div>
                    <div className="label" onClick={() => sortSubjects('code')}>
                        ΚΩΔΙΚΟΣ
                    </div>
                    <div className="label" onClick={() => sortSubjects('activeness')}>
                        ΕΝΕΡΓΟ
                    </div>
                    <div className="label" onClick={() => sortSubjects('period')}>
                        ΠΕΡΙΟΔΟΣ
                    </div>
                    <div className="label" onClick={() => sortSubjects('time')}>
                        ΧΡΟΝΟΣ
                    </div>
                </div>

                {subjects.map((subject, index) => (
                    <div key={index} className="subject">
                        <div className="SubjectName"onClick={() => toggleDetails(index)}>
                            {subject.name}
                            {subject.isOpen && (
                                <div className="extra-details">
                                    {subject.extraDetails.map((detail, detailIndex) => (
                                        <p key={detailIndex}>
                                            <strong>{detail.label}:</strong> {detail.value}
                                        </p>
                                    ))}
                                </div>
                            )}
                        </div>
                        <div>{subject.department}</div>
                        <div>{subject.code}</div>
                        <div>{subject.activeness}</div>
                        <div>{subject.period}</div>
                        <div>{subject.time}</div>
                    </div>
                ))}
            </div>
            <ProfHelpBar/>
        </div>
    );
}
