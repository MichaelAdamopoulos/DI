# File: makefile

exercise1 : exercise1.o functions.o
	gcc -o exercise1 exercise1.o functions.o

exercise1.o : exercise1.c types.h functions.h
	gcc -c -o exercise1.o exercise1.c

functions.o : functions.c types.h
	gcc -c -o functions.o functions.c

clean : 
	rm exercise1 exercise1.o functions.o

run : exercise1
	./exercise1
