# File: makefile

exercise3 : exercise3.o merge.o functions.o
	gcc -o exercise3 exercise3.o merge.o functions.o

exercise3.o : exercise3.c functions.h types.h
	gcc -c -o exercise3.o exercise3.c

merge.o : merge.c types.h
	gcc -c -o merge.o merge.c

functions.o : functions.c functions.h types.h
	gcc -c -o functions.o functions.c

clean :
	rm exercise3 exercise3.o merge.o functions.o

run : exercise3
	./exercise3


