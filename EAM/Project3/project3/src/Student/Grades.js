import React, { useState, useEffect } from "react";
import NavBar from "./NavBar";
import { Link } from "react-router-dom";
import HelpBar from "./HelpBar";
import "./Grades.css"

const examData = [
    {
        name: '1',
        period: 'ΧΕΙΜΕΡΙΝΟ',
        year: 2023,
        subjects: [
            { name: 'Ανάλυση Ι', grade: 7 },
            { name: 'Φυσική', grade: 4 },
            { name: 'Λογική Σχεδίαση', grade: 8 },
        ],
    },
    {
        name: '2',
        period: 'ΕΑΡΙΝΟ',
        year: 2023,
        subjects: [
            { name: 'Προγραμματισμός', grade: 8 },
            { name: 'Τεχνητή Νοημοσύνη', grade: 3 },
            { name: 'Μεταγγλωτιστές', grade: 6 },
        ],
    },
    {
        name: '3',
        period: 'ΣΕΜΠΤΕΒΡΙΟΥ',
        year: 2023,
        subjects: [
            { name: 'Τεχνητή Νοημοσύνη', grade: 6 },
            { name: 'Ανάλυση ΙΙ', grade: 7 },
            { name: 'Δομές Δεδομένων', grade: 4 },
        ],
    },
    {
        name: '4',
        period: 'ΧΕΙΜΕΡΙΝΟ',
        year: 2024,
        subjects: [
            { name: 'Δομές Δεδομένων', grade: 8 },
            { name: 'Γραμμική Άλγεβρα', grade: 5 },
            { name: 'Δίκτυα Υπολογιστών', grade: 7 },
        ],
    },
    {
        name: '5',
        period: 'ΕΑΡΙΝΟ',
        year: 2024,
        subjects: [
            { name: 'Θεωρία Αριθμών', grade: 9 },
            { name: 'Εισαγωγή στην Πληροφορική', grade: 2 },
            { name: 'Αντικειμενοστραφής Προγραμματισμός', grade: 7 },
        ],
    },
    {
        name: '6',
        period: 'ΣΕΜΠΤΕΒΡΙΟΥ',
        year: 2024,
        subjects: [
            { name: 'ΥΣΒΔ', grade: 7 },
            { name: 'ΣΧΒΔ', grade: 6 },
            { name: 'ΕΑΜ', grade: 5 },
        ],
    },
    {
        name: '7',
        period: 'ΧΕΙΜΕΡΙΝΟ',
        year: 2025,
        subjects: [
            { name: 'Αριθμητική Ανάλυση', grade: 6 },
            { name: 'Μαθηματικά Πληροφορικής', grade: 7 },
            { name: 'Αλγόριθμοι και Πολυπλοκότητα', grade: 8 },
        ],
    },
];

export default function Grades() {
    const [expandedExams, setExpandedExams] = useState([]);
    const [passFailFilter, setPassFailFilter] = useState('all');
    const [yearFilter, setYearFilter] = useState('all');
    const [periodFilter, setPeriodFilter] = useState('all');
    const [subjectFilter, setSubjectFilter] = useState('all');
    const [filteredExams, setFilteredExams] = useState([]);
    const [uniqueSubjects, setUniqueSubjects] = useState(new Set());
    const [uniqueYears, setUniqueYears] = useState(new Set());

    useEffect(() => {
        const subjectsSet = new Set(examData.flatMap((exam) => exam.subjects.map((subject) => subject.name)));
        setUniqueSubjects(subjectsSet);

        const yearsSet = new Set(examData.map((exam) => exam.year.toString()));
        setUniqueYears(yearsSet);
    }, []);

    useEffect(() => {
        const subjectFilteredExams = examData
            .filter((exam) => {
                const hasMatchingSubject = exam.subjects.some(
                    (subject) => subjectFilter === 'all' || subject.name === subjectFilter
                );

                const filteredSubjects = exam.subjects.filter((subject) => {
                    const isPass = subject.grade >= 5;
                    return (
                        (passFailFilter === 'pass' && isPass) ||
                        (passFailFilter === 'fail' && !isPass) ||
                        passFailFilter === 'all'
                    );
                });

                const shouldIncludeExam = filteredSubjects.length > 0;

                return (
                    (yearFilter === 'all' || exam.year.toString() === yearFilter) &&
                    (periodFilter === 'all' || exam.period === periodFilter) &&
                    hasMatchingSubject && shouldIncludeExam
                );
            })
            .map((exam) => {
                const filteredSubjects = exam.subjects.filter(
                    (subject) => (subjectFilter === 'all' || subject.name === subjectFilter) &&
                        ((passFailFilter === 'pass' && subject.grade >= 5) ||
                            (passFailFilter === 'fail' && subject.grade < 5) ||
                            passFailFilter === 'all')
                );

                return filteredSubjects.length > 0 ? { ...exam, subjects: filteredSubjects } : null;
            })
            .filter(Boolean);

        setFilteredExams(subjectFilteredExams);

        const filteredIndexes = subjectFilteredExams.map((_, index) => index);
        setExpandedExams(filteredIndexes);
    }, [passFailFilter, yearFilter, periodFilter, subjectFilter]);

    const handleSubjectFilterChange = (e) => {
        setSubjectFilter(e.target.value);
    };

    const clearFilters = () => {
        setPassFailFilter('all');
        setYearFilter('all');
        setPeriodFilter('all');
        setSubjectFilter('all');
        document.getElementById('passFailFilter').value = 'all';
        document.getElementById('yearFilter').value = 'all';
        document.getElementById('periodFilter').value = 'all';
        document.getElementById('subjectFilter').value = 'all';
    };

    const newarray = [...filteredExams];

    return (
        <div>
            <NavBar />
            <div className="Grades">
                <div className="Filters">
                    <label className="Pass/Fail">
                        Προσπάθειες:
                        <select id="passFailFilter" onChange={(e) => setPassFailFilter(e.target.value)}>
                            <option value="all">Όλα</option>
                            <option value="pass">Επιτυχής</option>
                            <option value="fail">Αποτυχής</option>
                        </select>
                    </label>
                    <label className="Year">
                        Έτος:
                        <select id="yearFilter" onChange={(e) => setYearFilter(e.target.value)}>
                            <option value="all">Όλα</option>
                            {[...uniqueYears].map((year, index) => (
                                <option key={index} value={year}>
                                    {year}
                                </option>
                            ))}
                        </select>
                    </label>
                    <label className="Period">
                        Περίοδος:
                        <select id="periodFilter" onChange={(e) => setPeriodFilter(e.target.value)}>
                            <option value="all">Όλα</option>
                            {['ΧΕΙΜΕΡΙΝΟ', 'ΕΑΡΙΝΟ', 'ΣΕΜΠΤΕΒΡΙΟΥ'].map((period, index) => (
                                <option key={index} value={period}>
                                    {period}
                                </option>
                            ))}
                        </select>
                    </label>
                    <label className="Subject">
                        Μάθημα:
                        <select id="subjectFilter" onChange={handleSubjectFilterChange}>
                            <option value="all">Όλα</option>
                            {[...uniqueSubjects].map((subject, index) => (
                                <option key={index} value={subject}>
                                    {subject}
                                </option>
                            ))}
                        </select>
                    </label>
                    <button onClick={clearFilters}>Καθαρισμός Φίλτρων</button>
                    <div className="PrintButton">
                        <Link to="/student/grades/print" state={{ hi: newarray }}>
                            Εκτύπωση
                        </Link>
                    </div>
                </div>
                <div className="Semesters">
                    {filteredExams.map((exam, index) => (
                        <div key={index} style={{ marginBottom: '15px' }}>
                            <div
                                style={{ cursor: 'pointer', fontWeight: 'bold' }}
                                onClick={() => setExpandedExams((prevExpandedExams) => (
                                    prevExpandedExams.includes(index)
                                        ? prevExpandedExams.filter((i) => i !== index)
                                        : [...prevExpandedExams, index]
                                ))}
                            >
                                {exam.period} {exam.year}
                            </div>
                            {expandedExams.includes(index) && (
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
                            )}
                        </div>
                    ))}
                </div>
            </div>
            <HelpBar />
        </div>
    );
}