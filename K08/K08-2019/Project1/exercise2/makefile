# File: makefile

exercise2 : exercise2.o functions.o
	gcc -o exercise2 exercise2.o functions.o

exercise2.o : exercise2.c types.h functions.h
	gcc -c -o exercise2.o exercise2.c

functions.o : functions.c types.h
	gcc -c -o functions.o functions.c

clean :
	rm exercise2 exercise2.o functions.o

run : exercise2
	./exercise2

