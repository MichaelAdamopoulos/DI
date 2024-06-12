# File: makefile

exercise4 : exercise4.o functions.o mergesort.o
	gcc -o exercise4 exercise4.o functions.o mergesort.o

exercise4.o : exercise4.c types.h functions.h
	gcc -c -o exercise4.o exercise4.c

functions.o : functions.c types.h
	gcc -c -o functions.o functions.c

mergesort.o :  mergesort.c types.h
	gcc -c -o mergesort.o mergesort.c

clean :
	rm exercise4 exercise4.o functions.o mergesort.o

run : exercise4
	./exercise4

