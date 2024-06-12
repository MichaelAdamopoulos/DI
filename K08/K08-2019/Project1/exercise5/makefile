# File: makefile

exercise5 : exercise5.o functions.o similar.o
	gcc -o exercise5 exercise5.o functions.o similar.o

exercise5.o : exercise5.c types.h functions.h
	gcc -c -o exercise5.o exercise5.c

functions.o : functions.c types.h
	gcc -c -o functions.o functions.c

similar.o : similar.c types.h functions.h
	gcc -c -o similar.o similar.c

clean :
	rm exercise5 exercise5.o functions.o similar.o

run : exercise5
	./exercise5

