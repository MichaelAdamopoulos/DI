# File: makefile

exercise1 : exercise1.o functions.o Queue.o
	gcc -o exercise1 exercise1.o functions.o Queue.o

exercise1.o : exercise1.c functions.h types.h
	gcc -c -o exercise1.o exercise1.c

functions.o : functions.c types.h QueueTypes.h QueueFunctions.h
	gcc -c -o functions.o functions.c

Queue.o : Queue.c types.h QueueTypes.h
	gcc -c -o Queue.o Queue.c

clean :
	rm exercise1 exercise1.o functions.o Queue.o

run : exercise1
	./exercise1

