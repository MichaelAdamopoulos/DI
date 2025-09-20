ΕΡΓΑΣΙΑ 2 ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΣΥΣΤΗΜΑΤΟΣ

ΑΔΑΜΟΠΟΥΛΟΣ ΜΙΧΑΗΛ 1115201800003

Παραδοτέα:

    - jobExecutorServer.c
    - jobCommander.c
    - Makefile
    - completion_report.pdf
    - README

Compile:

    Τρέχουμε στο main directory make ώστε να γίνουν compile τα αρχεία και 
    έπειτα οι εντολές εκτελούνται σύμφωνα με τις προδιαγραφές της άσκησης.

Σχεδιαστικές επιλογές:

    - Structs:

        Η δομή μιας δουλειάς:

            typedef struct {
                char *job;                  // εντολή πχ. ls -l
                int clientSocket;           // socket επικοινωνίας controller-commander
                char jobID[7];              // job_XX
            } Job;

        Η δομή της "ουράς" των δουλειών προς εκτέλεση:

            typedef struct {
                int bufferSize;             // μέγιστο μέγεθος
                int jobCount;               // τωρινό μέγεθος
                Job **Jobs;                 // πίνακας με δουλείες
            } Buffer;

    - Condition variables & mutexes:

        Χρησιμοποιούνται 3 condition variables: 
            
            - bufferNotFullCond / bufferNotEmptyCond: 

                Οι workers μποκάρονται έως ότου λάβουν signal ότι ο buffer δεν είναι άδειος(άρα έχει δουλειές προς εκτέλεση).
                Οι controllers μποκάρονται έως ότου λάβουν signal ότι ο buffer δεν είναι γεμάτος(άρα μπορούν να προσθέσουν δουλειά).
            
            - concurrencyCond:

                Για ενημέρωση των workers ότι άλλαξε το concurrency.

        Χρησιμοποιούνται 3 mutexes:

            - controllerMutex / workerMutex:

                Ένας μόνο controller ή worker έχει πρόσβαση στο εκάστοτε critical section που συνήθως αφορά αλλαγές ή προσβαση στον buffer.

            - concurrencyMutex:

                Για ασφαλή αλλαγή του concurrency.

        Χρησιμοποιούνται πολλές global μεταβλητές, ώστε όλα τα thread να έχουν πρόσβαση σε αυτές.


Οι υπόλοιπες και κυρίως λειτουργικές επίλογες περιγράφονται αναλυτικά με σχόλια κατά μήκος του κώδικα.
Σε γενικά πλαίσια η φιλοσοφία των προγραμμάτων και των συναρτήσεων ακολουθούν αυστηρά τα πρώτυπα της εργασίας.

