ΕΡΓΑΣΙΑ 2 ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ

ΑΔΑΜΟΠΟΥΛΟΣ ΜΙΧΑΗΛ 1115201800003

Επεξεργασμένα αρχεία:

ps.c:
	
	- Νέο αρχείο που καλεί το system call getpinfo

ps.h:
	
	- Νέο αρχείο που περιέχει τον ορισμό τοu struct pstat

proc.c:

	- Αλλαγή allocpoc:
	
		- Προσθήκη default priority

	- Προσθήκη setpriority και getpinfo

	- Αλλαγή scheduler

proc.h:

	- Προσθήκη πεδίου priority

sysproc.c:

	- Προσθήκη sys_setpriority και sys_getpinfo

syscall.c:

	- Προσθήκη απαραίτητων πρωτότυπων συναρτήσεων και mapping

syscall.h:

	- Προσθήκη απαραίτητων #define

defs.h

	- Προσθήκη απαραίτητων πρωτότυπων συναρτήσεων

user.h:

	- Προσθήκη απαραίτητων πρωτότυπων συναρτήσεων
	
usys.pl:

	- Προσθήκη assemply συναρτήσεων

priotest.c:

	- Comment out setpriority

Makefile:

	- Προσθήκη ps

Οι υπόλοιπες σχεδιαστικές επιλογές περιγράφονται με σχόλια κατά μήκως του κώδικα.