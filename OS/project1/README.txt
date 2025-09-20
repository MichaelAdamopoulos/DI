ΕΡΓΑΣΙΑ 1 ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ

ΜΙΧΑΗΛ ΑΔΑΜΟΠΟΥΛΟΣ - 1115201800003

Παραδοτέα:

- Makefile
- messenger.c

Compile and Run:

- Split terminal
- make
- ./messenger σε κάθε terminal

Προσομοίωση εκτέλεσης:

Αριστερό terminal:

Hello
This is process A running
I am going to send this text to process B
All that is necessary for a project for Operating Systems
Let's see what process B has to say

Δεξί terminal:

Hello
This is process B running
I am going to send this text to process A
I am better than process A
And now i am going to exit
#BYE#

Αποτελέσματα:

Αριστερό terminal:

Hello
This is process A running
I am going to send this text to process B
All that is necessary for a project for Operating Systems
Let's see what process B has to say
Hello
This is process B running
I am going to send this text to process A
I am better than process A
And now i am going to exit
#BYE#
Process A produced 5 messages
Process A consumed 6 messages
Process A produced 13 total packages with an average of 2.60 per message
Process A waited on average 2 seconds for each first packet

Δεξί terminal:

Hello
This is process A running
I am going to send this text to process B
All that is necessary for a project for Operating Systems
Let's see what process B has to say
Hello
This is process B running
I am going to send this text to process A
I am better than process A
And now i am going to exit
#BYE#
Process B produced 6 messages
Process B consumed 5 messages
Process B produced 11 total packages with an average of 1.83 per message
Process B waited on average 1 seconds for each first packet

Διαδικαστικές επιλογές και εξηγήσεις:

- Θεωρούμε ότι ο μέγιστος αριθμός χαρακτήρων που μπορούν να δωθούν σαν είσοδος είναι 10 x ΜΕΓΕΘΟΣ ΠΑΚΕΤΟΥ.
  (Έχουν γίνει define οι αντίστοιχες μεταβλητές ώστε να μπορεί να αλλαχθεί άμεσα για όλο το πρόγραμμα)

- Το πρόγραμμα τρέχει και με ανακτατεύθυνση εισόδο/εξόδου από/σε αρχείο.

Οι υπόλοιπες διαδικαστικές επιλογές εξηγούνται επαρκώς με σχόλια κατά μήκος του παραδοτέου κώδικα.

















