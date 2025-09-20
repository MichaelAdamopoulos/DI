import React, { useState } from 'react';
import './SubjectsDropdown.css';

const subjectsBySemesterAndOption = {
  1: {
    A: [
      {
        name: 'Μάθημα 1',
        code: 'Κωδικός 1',
        ects: 'ΕCTS 1',
        semester: 'Εξάμηνο 1',
        category: 'Κατηγορία 1',
        secondaryElement1: 'Σύγγραμμα 1',
        secondaryElement2: 'Διδάσκων Καθηγητής 1',
        secondaryElement3: 'Βαθμός Βάσης 1',
        secondaryElement4: 'Πτυχίο 1',
        secondaryElement5: 'Ώρες Διδασκαλίας 1',
        secondaryElement6: 'Φροντιστήρια 1',
        secondaryElement7: 'Εργαστήρια 1',
        secondaryElement8: 'Εργασίες 1',
        secondaryElement9: 'Σεμινάριο 1'
      },
      {
        name: 'Μάθημα 2',
        code: 'Κωδικός 2',
        ects: 'ΕCTS 2',
        semester: 'Εξάμηνο 2',
        category: 'Κατηγορία 2',
        secondaryElement1: 'Σύγγραμμα 2',
        secondaryElement2: 'Διδάσκων Καθηγητής 2',
        secondaryElement3: 'Βαθμός Βάσης 2',
        secondaryElement4: 'Πτυχίο 2',
        secondaryElement5: 'Ώρες Διδασκαλίας 2',
        secondaryElement6: 'Φροντιστήρια 2',
        secondaryElement7: 'Εργαστήρια 2',
        secondaryElement8: 'Εργασίες 2',
        secondaryElement9: 'Σεμινάριο 2'
      }
    ],
    B: [
      {
        name: 'Μάθημα 3',
        code: 'Κωδικός 3',
        ects: 'ΕCTS 3',
        semester: 'Εξάμηνο 3',
        category: 'Κατηγορία 3',
        secondaryElement1: 'Σύγγραμμα 3',
        secondaryElement2: 'Διδάσκων Καθηγητής 3',
        secondaryElement3: 'Βαθμός Βάσης 3',
        secondaryElement4: 'Πτυχίο 3',
        secondaryElement5: 'Ώρες Διδασκαλίας 3',
        secondaryElement6: 'Φροντιστήρια 3',
        secondaryElement7: 'Εργαστήρια 3',
        secondaryElement8: 'Εργασίες 3',
        secondaryElement9: 'Σεμινάριο 3'
      },
      {
        name: 'Μάθημα 4',
        code: 'Κωδικός 4',
        ects: 'ΕCTS 4',
        semester: 'Εξάμηνο 4',
        category: 'Κατηγορία 4',
        secondaryElement1: 'Σύγγραμμα 4',
        secondaryElement2: 'Διδάσκων Καθηγητής 4',
        secondaryElement3: 'Βαθμός Βάσης 4',
        secondaryElement4: 'Πτυχίο 4',
        secondaryElement5: 'Ώρες Διδασκαλίας 4',
        secondaryElement6: 'Φροντιστήρια 4',
        secondaryElement7: 'Εργαστήρια 4',
        secondaryElement8: 'Εργασίες 4',
        secondaryElement9: 'Σεμινάριο 4'
      }
    ]
  },
  2: {
    A: [
      {
        name: 'Μάθημα 5',
        code: 'Κωδικός 5',
        ects: 'ΕCTS 5',
        semester: 'Εξάμηνο 5',
        category: 'Κατηγορία 5',
        secondaryElement1: 'Σύγγραμμα 5',
        secondaryElement2: 'Διδάσκων Καθηγητής 5',
        secondaryElement3: 'Βαθμός Βάσης 5',
        secondaryElement4: 'Πτυχίο 5',
        secondaryElement5: 'Ώρες Διδασκαλίας 5',
        secondaryElement6: 'Φροντιστήρια 5',
        secondaryElement7: 'Εργαστήρια 5',
        secondaryElement8: 'Εργασίες 5',
        secondaryElement9: 'Σεμινάριο 5'
      },
      {
        name: 'Μάθημα 6',
        code: 'Κωδικός 6',
        ects: 'ΕCTS 6',
        semester: 'Εξάμηνο 6',
        category: 'Κατηγορία 6',
        secondaryElement1: 'Σύγγραμμα 6',
        secondaryElement2: 'Διδάσκων Καθηγητής 6',
        secondaryElement3: 'Βαθμός Βάσης 6',
        secondaryElement4: 'Πτυχίο 6',
        secondaryElement5: 'Ώρες Διδασκαλίας 6',
        secondaryElement6: 'Φροντιστήρια 6',
        secondaryElement7: 'Εργαστήρια 6',
        secondaryElement8: 'Εργασίες 6',
        secondaryElement9: 'Σεμινάριο 6'
      }
    ],
    B: [
      {
        name: 'Μάθημα 7',
        code: 'Κωδικός 7',
        ects: 'ΕCTS 7',
        semester: 'Εξάμηνο 7',
        category: 'Κατηγορία 7',
        secondaryElement1: 'Σύγγραμμα 7',
        secondaryElement2: 'Διδάσκων Καθηγητής 7',
        secondaryElement3: 'Βαθμός Βάσης 7',
        secondaryElement4: 'Πτυχίο 7',
        secondaryElement5: 'Ώρες Διδασκαλίας 7',
        secondaryElement6: 'Φροντιστήρια 7',
        secondaryElement7: 'Εργαστήρια 7',
        secondaryElement8: 'Εργασίες 7',
        secondaryElement9: 'Σεμινάριο 7'
      },
      {
        name: 'Μάθημα 8',
        code: 'Κωδικός 8',
        ects: 'ΕCTS 8',
        semester: 'Εξάμηνο 8',
        category: 'Κατηγορία 8',
        secondaryElement1: 'Σύγγραμμα 8',
        secondaryElement2: 'Διδάσκων Καθηγητής 8',
        secondaryElement3: 'Βαθμός Βάσης 8',
        secondaryElement4: 'Πτυχίο 8',
        secondaryElement5: 'Ώρες Διδασκαλίας 8',
        secondaryElement6: 'Φροντιστήρια 8',
        secondaryElement7: 'Εργαστήρια 8',
        secondaryElement8: 'Εργασίες 8',
        secondaryElement9: 'Σεμινάριο 8'
      }
    ]
  },
  3: {
    A: [
      {
        name: 'Μάθημα 9',
        code: 'Κωδικός 9',
        ects: 'ΕCTS 9',
        semester: 'Εξάμηνο 9',
        category: 'Κατηγορία 9',
        secondaryElement1: 'Σύγγραμμα 9',
        secondaryElement2: 'Διδάσκων Καθηγητής 9',
        secondaryElement3: 'Βαθμός Βάσης 9',
        secondaryElement4: 'Πτυχίο 9',
        secondaryElement5: 'Ώρες Διδασκαλίας 9',
        secondaryElement6: 'Φροντιστήρια 9',
        secondaryElement7: 'Εργαστήρια 9',
        secondaryElement8: 'Εργασίες 9',
        secondaryElement9: 'Σεμινάριο 9'
      },
      {
        name: 'Μάθημα 10',
        code: 'Κωδικός 10',
        ects: 'ΕCTS 10',
        semester: 'Εξάμηνο 10',
        category: 'Κατηγορία 10',
        secondaryElement1: 'Σύγγραμμα 10',
        secondaryElement2: 'Διδάσκων Καθηγητής 10',
        secondaryElement3: 'Βαθμός Βάσης 10',
        secondaryElement4: 'Πτυχίο 10',
        secondaryElement5: 'Ώρες Διδασκαλίας 10',
        secondaryElement6: 'Φροντιστήρια 10',
        secondaryElement7: 'Εργαστήρια 10',
        secondaryElement8: 'Εργασίες 10',
        secondaryElement9: 'Σεμινάριο 10'
      }
    ],
    B: [
      {
        name: 'Μάθημα 11',
        code: 'Κωδικός 11',
        ects: 'ΕCTS 11',
        semester: 'Εξάμηνο 11',
        category: 'Κατηγορία 11',
        secondaryElement1: 'Σύγγραμμα 11',
        secondaryElement2: 'Διδάσκων Καθηγητής 11',
        secondaryElement3: 'Βαθμός Βάσης 11',
        secondaryElement4: 'Πτυχίο 11',
        secondaryElement5: 'Ώρες Διδασκαλίας 11',
        secondaryElement6: 'Φροντιστήρια 11',
        secondaryElement7: 'Εργαστήρια 11',
        secondaryElement8: 'Εργασίες 11',
        secondaryElement9: 'Σεμινάριο 11'
      },
      {
        name: 'Μάθημα 12',
        code: 'Κωδικός 12',
        ects: 'ΕCTS 12',
        semester: 'Εξάμηνο 12',
        category: 'Κατηγορία 12',
        secondaryElement1: 'Σύγγραμμα 12',
        secondaryElement2: 'Διδάσκων Καθηγητής 12',
        secondaryElement3: 'Βαθμός Βάσης 12',
        secondaryElement4: 'Πτυχίο 12',
        secondaryElement5: 'Ώρες Διδασκαλίας 12',
        secondaryElement6: 'Φροντιστήρια 12',
        secondaryElement7: 'Εργαστήρια 12',
        secondaryElement8: 'Εργασίες 12',
        secondaryElement9: 'Σεμινάριο 12'
      }
    ]
  },
  4: {
    A: [
      {
        name: 'Μάθημα 13',
        code: 'Κωδικός 13',
        ects: 'ΕCTS 13',
        semester: 'Εξάμηνο 13',
        category: 'Κατηγορία 13',
        secondaryElement1: 'Σύγγραμμα 13',
        secondaryElement2: 'Διδάσκων Καθηγητής 13',
        secondaryElement3: 'Βαθμός Βάσης 13',
        secondaryElement4: 'Πτυχίο 13',
        secondaryElement5: 'Ώρες Διδασκαλίας 13',
        secondaryElement6: 'Φροντιστήρια 13',
        secondaryElement7: 'Εργαστήρια 13',
        secondaryElement8: 'Εργασίες 13',
        secondaryElement9: 'Σεμινάριο 13'
      },
      {
        name: 'Μάθημα 14',
        code: 'Κωδικός 14',
        ects: 'ΕCTS 14',
        semester: 'Εξάμηνο 14',
        category: 'Κατηγορία 14',
        secondaryElement1: 'Σύγγραμμα 14',
        secondaryElement2: 'Διδάσκων Καθηγητής 14',
        secondaryElement3: 'Βαθμός Βάσης 14',
        secondaryElement4: 'Πτυχίο 14',
        secondaryElement5: 'Ώρες Διδασκαλίας 14',
        secondaryElement6: 'Φροντιστήρια 14',
        secondaryElement7: 'Εργαστήρια 14',
        secondaryElement8: 'Εργασίες 14',
        secondaryElement9: 'Σεμινάριο 14'
      }
    ],
    B: [
      {
        name: 'Μάθημα 15',
        code: 'Κωδικός 15',
        ects: 'ΕCTS 15',
        semester: 'Εξάμηνο 15',
        category: 'Κατηγορία 15',
        secondaryElement1: 'Σύγγραμμα 15',
        secondaryElement2: 'Διδάσκων Καθηγητής 15',
        secondaryElement3: 'Βαθμός Βάσης 15',
        secondaryElement4: 'Πτυχίο 15',
        secondaryElement5: 'Ώρες Διδασκαλίας 15',
        secondaryElement6: 'Φροντιστήρια 15',
        secondaryElement7: 'Εργαστήρια 15',
        secondaryElement8: 'Εργασίες 15',
        secondaryElement9: 'Σεμινάριο 15'
      },
      {
        name: 'Μάθημα 16',
        code: 'Κωδικός 16',
        ects: 'ΕCTS 16',
        semester: 'Εξάμηνο 16',
        category: 'Κατηγορία 16',
        secondaryElement1: 'Σύγγραμμα 16',
        secondaryElement2: 'Διδάσκων Καθηγητής 16',
        secondaryElement3: 'Βαθμός Βάσης 16',
        secondaryElement4: 'Πτυχίο 16',
        secondaryElement5: 'Ώρες Διδασκαλίας 16',
        secondaryElement6: 'Φροντιστήρια 16',
        secondaryElement7: 'Εργαστήρια 16',
        secondaryElement8: 'Εργασίες 16',
        secondaryElement9: 'Σεμινάριο 16'
      }
    ]
  },
  5: {
    A: [
      {
        name: 'Μάθημα 17',
        code: 'Κωδικός 17',
        ects: 'ΕCTS 17',
        semester: 'Εξάμηνο 17',
        category: 'Κατηγορία 17',
        secondaryElement1: 'Σύγγραμμα 17',
        secondaryElement2: 'Διδάσκων Καθηγητής 17',
        secondaryElement3: 'Βαθμός Βάσης 17',
        secondaryElement4: 'Πτυχίο 17',
        secondaryElement5: 'Ώρες Διδασκαλίας 17',
        secondaryElement6: 'Φροντιστήρια 17',
        secondaryElement7: 'Εργαστήρια 17',
        secondaryElement8: 'Εργασίες 17',
        secondaryElement9: 'Σεμινάριο 17'
      },
      {
        name: 'Μάθημα 18',
        code: 'Κωδικός 18',
        ects: 'ΕCTS 18',
        semester: 'Εξάμηνο 18',
        category: 'Κατηγορία 18',
        secondaryElement1: 'Σύγγραμμα 18',
        secondaryElement2: 'Διδάσκων Καθηγητής 18',
        secondaryElement3: 'Βαθμός Βάσης 18',
        secondaryElement4: 'Πτυχίο 18',
        secondaryElement5: 'Ώρες Διδασκαλίας 18',
        secondaryElement6: 'Φροντιστήρια 18',
        secondaryElement7: 'Εργαστήρια 18',
        secondaryElement8: 'Εργασίες 18',
        secondaryElement9: 'Σεμινάριο 18'
      }
    ],
    B: [
      {
        name: 'Μάθημα 19',
        code: 'Κωδικός 19',
        ects: 'ΕCTS 19',
        semester: 'Εξάμηνο 19',
        category: 'Κατηγορία 19',
        secondaryElement1: 'Σύγγραμμα 19',
        secondaryElement2: 'Διδάσκων Καθηγητής 19',
        secondaryElement3: 'Βαθμός Βάσης 19',
        secondaryElement4: 'Πτυχίο 19',
        secondaryElement5: 'Ώρες Διδασκαλίας 19',
        secondaryElement6: 'Φροντιστήρια 19',
        secondaryElement7: 'Εργαστήρια 19',
        secondaryElement8: 'Εργασίες 19',
        secondaryElement9: 'Σεμινάριο 19'
      },
      {
        name: 'Μάθημα 20',
        code: 'Κωδικός 20',
        ects: 'ΕCTS 20',
        semester: 'Εξάμηνο 20',
        category: 'Κατηγορία 20',
        secondaryElement1: 'Σύγγραμμα 20',
        secondaryElement2: 'Διδάσκων Καθηγητής 20',
        secondaryElement3: 'Βαθμός Βάσης 20',
        secondaryElement4: 'Πτυχίο 20',
        secondaryElement5: 'Ώρες Διδασκαλίας 20',
        secondaryElement6: 'Φροντιστήρια 20',
        secondaryElement7: 'Εργαστήρια 20',
        secondaryElement8: 'Εργασίες 20',
        secondaryElement9: 'Σεμινάριο 20'
      }
    ]
  },
  6: {
    A: [
      {
        name: 'Μάθημα 21',
        code: 'Κωδικός 21',
        ects: 'ΕCTS 21',
        semester: 'Εξάμηνο 21',
        category: 'Κατηγορία 21',
        secondaryElement1: 'Σύγγραμμα 21',
        secondaryElement2: 'Διδάσκων Καθηγητής 21',
        secondaryElement3: 'Βαθμός Βάσης 21',
        secondaryElement4: 'Πτυχίο 21',
        secondaryElement5: 'Ώρες Διδασκαλίας 21',
        secondaryElement6: 'Φροντιστήρια 21',
        secondaryElement7: 'Εργαστήρια 21',
        secondaryElement8: 'Εργασίες 21',
        secondaryElement9: 'Σεμινάριο 21'
      },
      {
        name: 'Μάθημα 22',
        code: 'Κωδικός 22',
        ects: 'ΕCTS 22',
        semester: 'Εξάμηνο 22',
        category: 'Κατηγορία 22',
        secondaryElement1: 'Σύγγραμμα 22',
        secondaryElement2: 'Διδάσκων Καθηγητής 22',
        secondaryElement3: 'Βαθμός Βάσης 22',
        secondaryElement4: 'Πτυχίο 22',
        secondaryElement5: 'Ώρες Διδασκαλίας 22',
        secondaryElement6: 'Φροντιστήρια 22',
        secondaryElement7: 'Εργαστήρια 22',
        secondaryElement8: 'Εργασίες 22',
        secondaryElement9: 'Σεμινάριο 22'
      }
    ],
    B: [
      {
        name: 'Μάθημα 23',
        code: 'Κωδικός 23',
        ects: 'ΕCTS 23',
        semester: 'Εξάμηνο 23',
        category: 'Κατηγορία 23',
        secondaryElement1: 'Σύγγραμμα 23',
        secondaryElement2: 'Διδάσκων Καθηγητής 23',
        secondaryElement3: 'Βαθμός Βάσης 23',
        secondaryElement4: 'Πτυχίο 23',
        secondaryElement5: 'Ώρες Διδασκαλίας 23',
        secondaryElement6: 'Φροντιστήρια 23',
        secondaryElement7: 'Εργαστήρια 23',
        secondaryElement8: 'Εργασίες 23',
        secondaryElement9: 'Σεμινάριο 23'
      },
      {
        name: 'Μάθημα 24',
        code: 'Κωδικός 24',
        ects: 'ΕCTS 24',
        semester: 'Εξάμηνο 24',
        category: 'Κατηγορία 24',
        secondaryElement1: 'Σύγγραμμα 24',
        secondaryElement2: 'Διδάσκων Καθηγητής 24',
        secondaryElement3: 'Βαθμός Βάσης 24',
        secondaryElement4: 'Πτυχίο 24',
        secondaryElement5: 'Ώρες Διδασκαλίας 24',
        secondaryElement6: 'Φροντιστήρια 24',
        secondaryElement7: 'Εργαστήρια 24',
        secondaryElement8: 'Εργασίες 24',
        secondaryElement9: 'Σεμινάριο 24'
      }
    ]
  },
  7: {
    A: [
      {
        name: 'Μάθημα 25',
        code: 'Κωδικός 25',
        ects: 'ΕCTS 25',
        semester: 'Εξάμηνο 25',
        category: 'Κατηγορία 25',
        secondaryElement1: 'Σύγγραμμα 25',
        secondaryElement2: 'Διδάσκων Καθηγητής 25',
        secondaryElement3: 'Βαθμός Βάσης 25',
        secondaryElement4: 'Πτυχίο 25',
        secondaryElement5: 'Ώρες Διδασκαλίας 25',
        secondaryElement6: 'Φροντιστήρια 25',
        secondaryElement7: 'Εργαστήρια 25',
        secondaryElement8: 'Εργασίες 25',
        secondaryElement9: 'Σεμινάριο 25'
      },
      {
        name: 'Μάθημα 26',
        code: 'Κωδικός 26',
        ects: 'ΕCTS 26',
        semester: 'Εξάμηνο 26',
        category: 'Κατηγορία 26',
        secondaryElement1: 'Σύγγραμμα 26',
        secondaryElement2: 'Διδάσκων Καθηγητής 26',
        secondaryElement3: 'Βαθμός Βάσης 26',
        secondaryElement4: 'Πτυχίο 26',
        secondaryElement5: 'Ώρες Διδασκαλίας 26',
        secondaryElement6: 'Φροντιστήρια 26',
        secondaryElement7: 'Εργαστήρια 26',
        secondaryElement8: 'Εργασίες 26',
        secondaryElement9: 'Σεμινάριο 26'
      }
    ],
    B: [
      {
        name: 'Μάθημα 27',
        code: 'Κωδικός 27',
        ects: 'ΕCTS 27',
        semester: 'Εξάμηνο 27',
        category: 'Κατηγορία 27',
        secondaryElement1: 'Σύγγραμμα 27',
        secondaryElement2: 'Διδάσκων Καθηγητής 27',
        secondaryElement3: 'Βαθμός Βάσης 27',
        secondaryElement4: 'Πτυχίο 27',
        secondaryElement5: 'Ώρες Διδασκαλίας 27',
        secondaryElement6: 'Φροντιστήρια 27',
        secondaryElement7: 'Εργαστήρια 27',
        secondaryElement8: 'Εργασίες 27',
        secondaryElement9: 'Σεμινάριο 27'
      },
      {
        name: 'Μάθημα 28',
        code: 'Κωδικός 28',
        ects: 'ΕCTS 28',
        semester: 'Εξάμηνο 28',
        category: 'Κατηγορία 28',
        secondaryElement1: 'Σύγγραμμα 28',
        secondaryElement2: 'Διδάσκων Καθηγητής 28',
        secondaryElement3: 'Βαθμός Βάσης 28',
        secondaryElement4: 'Πτυχίο 28',
        secondaryElement5: 'Ώρες Διδασκαλίας 28',
        secondaryElement6: 'Φροντιστήρια 28',
        secondaryElement7: 'Εργαστήρια 28',
        secondaryElement8: 'Εργασίες 28',
        secondaryElement9: 'Σεμινάριο 28'
      }
    ]
  },
  8: {
    A: [
      {
        name: 'Μάθημα 29',
        code: 'Κωδικός 29',
        ects: 'ΕCTS 29',
        semester: 'Εξάμηνο 29',
        category: 'Κατηγορία 29',
        secondaryElement1: 'Σύγγραμμα 29',
        secondaryElement2: 'Διδάσκων Καθηγητής 29',
        secondaryElement3: 'Βαθμός Βάσης 29',
        secondaryElement4: 'Πτυχίο 29',
        secondaryElement5: 'Ώρες Διδασκαλίας 29',
        secondaryElement6: 'Φροντιστήρια 29',
        secondaryElement7: 'Εργαστήρια 29',
        secondaryElement8: 'Εργασίες 29',
        secondaryElement9: 'Σεμινάριο 29'
      },
      {
        name: 'Μάθημα 30',
        code: 'Κωδικός 30',
        ects: 'ΕCTS 30',
        semester: 'Εξάμηνο 30',
        category: 'Κατηγορία 30',
        secondaryElement1: 'Σύγγραμμα 30',
        secondaryElement2: 'Διδάσκων Καθηγητής 30',
        secondaryElement3: 'Βαθμός Βάσης 30',
        secondaryElement4: 'Πτυχίο 30',
        secondaryElement5: 'Ώρες Διδασκαλίας 30',
        secondaryElement6: 'Φροντιστήρια 30',
        secondaryElement7: 'Εργαστήρια 30',
        secondaryElement8: 'Εργασίες 30',
        secondaryElement9: 'Σεμινάριο 30'
      }
    ],
    B: [
      {
        name: 'Μάθημα 31',
        code: 'Κωδικός 31',
        ects: 'ΕCTS 31',
        semester: 'Εξάμηνο 31',
        category: 'Κατηγορία 31',
        secondaryElement1: 'Σύγγραμμα 31',
        secondaryElement2: 'Διδάσκων Καθηγητής 31',
        secondaryElement3: 'Βαθμός Βάσης 31',
        secondaryElement4: 'Πτυχίο 31',
        secondaryElement5: 'Ώρες Διδασκαλίας 31',
        secondaryElement6: 'Φροντιστήρια 31',
        secondaryElement7: 'Εργαστήρια 31',
        secondaryElement8: 'Εργασίες 31',
        secondaryElement9: 'Σεμινάριο 31'
      },
      {
        name: 'Μάθημα 32',
        code: 'Κωδικός 32',
        ects: 'ΕCTS 32',
        semester: 'Εξάμηνο 32',
        category: 'Κατηγορία 32',
        secondaryElement1: 'Σύγγραμμα 32',
        secondaryElement2: 'Διδάσκων Καθηγητής 32',
        secondaryElement3: 'Βαθμός Βάσης 32',
        secondaryElement4: 'Πτυχίο 32',
        secondaryElement5: 'Ώρες Διδασκαλίας 32',
        secondaryElement6: 'Φροντιστήρια 32',
        secondaryElement7: 'Εργαστήρια 32',
        secondaryElement8: 'Εργασίες 32',
        secondaryElement9: 'Σεμινάριο 32'
      }
    ]
  }
};

const SubjectDetails = ({ subjects, onRemove, onRemoveAll, onToggleDetails }) => {
  return (
    <div className="subject-details">
      {subjects.length > 0 && (
        <table>
          <thead>
            <tr>
              <th>ΜΑΘΗΜΑ</th>
              <th>ΚΩΔΙΚΟΣ</th>
              <th>ECTS</th>
              <th>ΕΞΑΜΗΝΟ</th>
              <th>ΚΑΤΗΓΟΡΙΑ</th>
            </tr>
          </thead>
          <tbody>
            {subjects.map((subject) => (
              <React.Fragment key={subject.name}>
                <tr>
                  <td>{subject.name}</td>
                  <td>{subject.code}</td>
                  <td>{subject.ects}</td>
                  <td>{subject.semester}</td>
                  <td>{subject.category}</td>
                  <td>
                    <button className="button1" onClick={() => onToggleDetails(subject)}>
                      {subject.isExpanded ? 'Λιγότερα' : 'Περισσότερα'}
                    </button>
                  </td>
                  <td>
                    <button className="button2" onClick={() => onRemove(subject.name)}>
                      x
                    </button>
                  </td>
                </tr>
                {subject.isExpanded && (
                  <tr>
                    <td>
                      <div className="secondary-elements">
                        <p>
                          <strong>Σύγγραμμα:</strong> {subject.secondaryElement1}
                        </p>
                        <p>
                          <strong>Διδάσκων Καθηγητής:</strong> {subject.secondaryElement2}
                        </p>
                        <p>
                          <strong> Βαθμός Βάσης:</strong> {subject.secondaryElement3}
                        </p>
                        <p>
                          <strong>Υπολογίζεται στον Βαθμό του Πτυχίου:</strong> {subject.secondaryElement4}
                        </p>
                        <p>
                          <strong>Ώρες Διδασκαλίας:</strong> {subject.secondaryElement5}
                        </p>
                        <p>
                          <strong>Φροντιστήρια:</strong> {subject.secondaryElement6}
                        </p>
                        <p>
                          <strong>Εργαστήρια:</strong> {subject.secondaryElement7}
                        </p>
                        <p>
                          <strong>Εργασίες:</strong> {subject.secondaryElement8}
                        </p>
                        <p>
                          <strong>Σεμινάριο:</strong> {subject.secondaryElement9}
                        </p>
                      </div>
                    </td>
                  </tr>
                )}
              </React.Fragment>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
};

const DropdownMenu = () => {
  const [openSemesters, setOpenSemesters] = useState([]);
  const [openCategories, setOpenCategories] = useState([]);
  const [selectedSubjects, setSelectedSubjects] = useState([]);
  const [searchQuery, setSearchQuery] = useState('');
  const [searchResults, setSearchResults] = useState([]);

  const handleSemesterClick = (semester) => {
    setOpenSemesters((prevOpenSemesters) =>
      prevOpenSemesters.includes(semester)
        ? prevOpenSemesters.filter((s) => s !== semester)
        : [...prevOpenSemesters, semester]
    );
    setOpenCategories([]);
  };

  const handleCategoryClick = (category) => {
    setOpenCategories((prevOpenCategories) =>
      prevOpenCategories.includes(category)
        ? prevOpenCategories.filter((c) => c !== category)
        : [...prevOpenCategories, category]
    );
  };

  const handleSubjectClick = (subject) => {
    const isAlreadySelected = selectedSubjects.some((s) => s.name === subject.name);

    if (isAlreadySelected) {
      setSelectedSubjects((prevSelectedSubjects) =>
        prevSelectedSubjects.filter((s) => s.name !== subject.name)
      );
    } else {
      setSelectedSubjects((prevSelectedSubjects) =>
        prevSelectedSubjects.some((s) => s.name === subject.name)
          ? prevSelectedSubjects
          : [...prevSelectedSubjects, { ...subject, isExpanded: false }]
      );
    }
  };

  const handleRemoveSubject = (subjectName) => {
    setSelectedSubjects((prevSelectedSubjects) =>
      prevSelectedSubjects.filter((s) => s.name !== subjectName)
    );
  };

  const handleRemoveAllSubjects = () => {
    setSelectedSubjects([]);
  };

  const handleToggleDetails = (subject) => {
    setSelectedSubjects((prevSelectedSubjects) =>
      prevSelectedSubjects.map((s) =>
        s.name === subject.name ? { ...s, isExpanded: !s.isExpanded } : s
      )
    );
  };

  const handleSearchChange = (event) => {
    const query = event.target.value.toLowerCase();
    setSearchQuery(query);

    const allSubjects = Object.values(subjectsBySemesterAndOption).flatMap((options) =>
      Object.values(options).flatMap((subjects) => subjects)
    );

    const results = query
      ? allSubjects.filter((subject) => subject.name.toLowerCase().includes(query))
      : [];

    setSearchResults(results);
  };

  return (
    <div className="dropdown-menu-container">
      <div className="search-form">
        <label className="dropdown-label">Αναζήτηση Μαθήματος:</label>
        <input
          type="text"
          value={searchQuery}
          onChange={handleSearchChange}
          placeholder="Μάθημα"
        />
        {searchResults.length > 0 && (
          <ul className="search-results">
            {searchResults.map((result) => (
              <li key={result.name} onClick={() => handleSubjectClick(result)}>
                {result.name}
              </li>
            ))}
          </ul>
        )}
      </div>

      <div className="subjects-details-container">
        <ul className="semester-list">
          {Object.keys(subjectsBySemesterAndOption).map((semester) => (
            <li key={semester}>
              <span
                className={`clickable-text ${openSemesters.includes(semester) && 'open'}`}
                onClick={() => handleSemesterClick(semester)}
              >
                Εξάμηνο {semester}
              </span>
              {openSemesters.includes(semester) && (
                <ul className="category-list">
                  {['A', 'B'].map((category) => (
                    <li key={category}>
                      <span
                        className={`clickable-text ${openCategories.includes(category) && 'open'}`}
                        onClick={() => handleCategoryClick(category)}
                      >
                        Κατηγορία {category}
                      </span>
                      {openCategories.includes(category) && (
                        <ul className="subject-list">
                          {(subjectsBySemesterAndOption[semester]?.[category] || []).map(
                            (subject) => (
                              <li key={subject.name} onClick={() => handleSubjectClick(subject)}>
                                <span className="clickable-text">{subject.name}</span>
                                {subject.isExpanded && (
                                  <div className="secondary-elements">
                                    <p>{subject.secondaryElement1}</p>
                                    <p>{subject.secondaryElement2}</p>
                                    <p>{subject.secondaryElement3}</p>
                                    <p>{subject.secondaryElement4}</p>
                                    <p>{subject.secondaryElement5}</p>
                                    <p>{subject.secondaryElement6}</p>
                                    <p>{subject.secondaryElement7}</p>
                                    <p>{subject.secondaryElement8}</p>
                                    <p>{subject.secondaryElement9}</p>
                                  </div>
                                )}
                              </li>
                            )
                          )}
                        </ul>
                      )}
                    </li>
                  ))}
                </ul>
              )}
            </li>
          ))}
        </ul>
        <div className="SubjectDetails">                 
          {selectedSubjects.length > 0 && (
            <SubjectDetails
              subjects={selectedSubjects}
              onRemove={handleRemoveSubject}
              onRemoveAll={handleRemoveAllSubjects}
              onToggleDetails={handleToggleDetails}
            />
          )}
        </div>
        
      </div>
    </div>
  );
};

export default DropdownMenu;