# File: makefile

exercise6 : exercise6.o functions.o conversion.o
	gcc -o exercise6 exercise6.o functions.o conversion.o

exercise6.o : exercise6.c types.h functions.h
	gcc -c -o exercise6.o exercise6.c

functions.o : functions.c types.h
	gcc -c -o functions.o functions.c

conversion.o : conversion.c types.h functions.h
	gcc -c -o conversion.o conversion.c

clean :
	rm exercise6 exercise6.o functions.o conversion.o

run : exercise6
	./exercise6
