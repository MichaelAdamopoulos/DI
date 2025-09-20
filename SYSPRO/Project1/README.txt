ΕΡΓΑΣΙΑ 1 ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΣΥΣΤΗΜΑΤΟΣ

ΑΔΑΜΟΠΟΥΛΟΣ ΜΙΧΑΗΛ 1115201800003

Παραδοτέα:

	- jobCommander.c
	- jobExecutorServer.c
	- queue.c
	- Makefile
	- multijob.sh
	- allJobsStop.sh
	- completion_report.pdf
	- README
	- include(directory)
		- jobExecutorServer.h
		- jobCommander.h
		- queue.h

Compile:

	Τρέχουμε στο main directory make ώστε να γίνουν compile τα αρχεία και 
	έπειτα οι εντολές εκτελούνται σύμφωνα με τις προδιαγραφές της άσκησης.

	Ο jobCommander μπορεί να εκτελεστεί από οποιοδήποτε path ή/και ως ./jobCommander.

Ενδεικτική εκτέλεση:
	(Χωρίς το printf στην progDelay(μόνο sleep) ώστε να είναι "καθαρό" το output του terminal)
	
	Input:

		jobCommander issueJob progDelay 1000
		jobCommander issueJob progDelay 1000
		jobCommander issueJob progDelay 1000
		jobCommander poll running
		jobCommander poll queued
		jobCommander setConcurrency 2
		jobCommander poll running
		jobCommander poll queued
		jobCommander setConcurrency 2
		jobCommander stop job_1
		jobCommander poll running
		jobCommander poll queued
		jobCommander stop job_3
		jobCommander stop job_2
		jobCommander exit

	Output:

		<job_1,progDelay 1000,1>

		<job_2,progDelay 1000,1>

		<job_3,progDelay 1000,2>

		<job_1,progDelay 1000,1>

		<job_2,progDelay 1000,1>
		<job_3,progDelay 1000,2>

		<job_1,progDelay 1000,1>
		<job_2,progDelay 1000,1>

		<job_3,progDelay 1000,2>

		job_1 terminated

		<job_2,progDelay 1000,1>

		<job_3,progDelay 1000,2>

		job_3 removed

		job_2 terminated

		jobExecutorServer terminated

Σχεδιαστικές επιλογές:

	- Χρησιμοποιούνται 2 structs:

		- struct Jobs {
    			struct Queue *queuedJobs;
    			struct Queue *runningJobs;
    			int concurrency;
    			int ids;
		  };

			Περιγράφει την δομή που "παρακολουθεί" τα jobs, περιέχοντας 2 ουρές, μία για running και
			μια για queued, το concurrency και το εκάστοτε id που θα αποκτήσει το κάθε νέο job
			(αυξάνεται κατά ένα μετά την είσοδο job στο σύστημα, χωρίς απαραίτητα αυτό να εκτελέστεί).

			Υποθέτουμε ότι αν ένα job μπει πχ. στην ουρά queued με position 1, μπορεί να μεταφερθεί άμεσα στην
			running αν υπάρχει δυνατότητα και το επόμενο job που θα έρθει θα μπει στην queued με position πάλι 1
			εφόσον αυτή άδειασε αμέσως.

		- struct Job {
    			char *jobID;
    			char **job;
    			int queuePosition;
    			int pid;
    			char *info;
		  };
		
			Περιγράφει ένα job, περιλαμβάνοντας το jobID(string σε μορφή job_XX), το job που αποτελεί
			τις εντολές προς εκτέλεση ως πίνακα(πχ. [ls, -l]), το queuePosition, που είναι η θέση που μπήκε
			στην queued ουρά, το pid της διεργασίας όταν αρχίσει να εκτελείται(εναλλατικά -1) και το info
			που είναι η πληροφορία προς εκτύπωση της μορφής πχ. <job_15, ls -l, 5>.

	- Στα αρχεία queue.c/queue.h υπάρχει η υλοποίηση των συναρτήσεων για ουρά.
	  

	- Υπάρχει έλεγχος στην είσοδο του χρήστη, ακριβώς σύμφωνα με τις προδιαγραφές τις άσκησης.
	  Οποιαδήποτε είσοδος που παρεκλείνει σε αριθμό ορισμάτων ή στον τύπο(πχ. issJob ή stop bla ή
	  poll ή job_AA) θα τυπώσει μήνυμα λάθους χωρίς να εκτελεστεί τίποτα, ούτε να ξεκινήσει ο
	  server. Εξαίρεση αποτελούν τα ορίσματα της issueJob που θα βγάλουν λάθος από την exec.


Η γενική φιλοσοφία του προγράμματος έχει ως εξής: Ξεκινάει ο commander, ελέγχει αν υπάρχει ο server και τον
δημιουργεί αν όχι. Έπειτα κάνει pause αν είναι κλειστός o server μέχρι να ανοίξει, έχοντας δημιουργήσει τις 2 FIFO.
Στην μία, command, γράφει ο commander και διαβάζει ο server τα jobs και στην άλλη, info, ανάποδα, επιστρέφει το
αποτέλεσμα ο server στον commander. Αφού γράψει, διαβάσει και εκτυπώσει ο commander τερματίζει. Ο δε server,
βρίσκεται σε μία κατάσταση αδράνειας(pause) έως ότου είτε λάβει command, είτε κάποιο job τερματίσει ή γίνει kill.
Τότε "ξυπνάει", διαβάζει από το command pipe όλες τις εντολές που υπάρχουν(μπορεί να έχουν έρθει πολλές ταυτόχρονα),
τις εκτελεί και γεμίζει την ουρά queued. Έπειτα "μαζεύει" όλα τα jobs που τερμάτισαν ή έγιναν kill(μπορεί να είναι
πολλά ταυτόχρονα), τα αφαιρεί απο την ουρά running και αρχίζει να εκτελεί ένα ένα τα jobs της queued, βγάζοντας τα
από την queued και βάζοντας τα στην running, σύμφωνα με το concurrency. Μόλις λάβει exit, τερματίζει αμέσως κλείνοντας
και σβήνοντας τις FIFO και το txt. O server στέλνει signal στον commander ότι άνοιξε, ο commander στέλνει signal στον
server ότι του έστειλε command και ο server λαμβάνει signal για τον τερματισμό ή το kill των jobs.Τις περισσότερες φορές
ο server ή ο commander θα αποστείλει στον άλλον αντίστοιχα, πρώτα το μέγεθος της πληροφορίας και μετά την ίδια την πληροφορία,
ώστε να μην υπάρχει περίπτωση να γράφουν/διαβάζουν περισσότερα/λιγότερα bytes από ότι πρέπει.
		



		

	

	

