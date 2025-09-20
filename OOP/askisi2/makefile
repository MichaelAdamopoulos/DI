# File: makefile

main: main.o class.o tree.o list.o
	g++ -o main main.o class.o tree.o list.o

main.o: main.cpp class.h tree.h list.h
	g++ -c main.cpp

class.o: class.cpp class.h tree.h list.h
	g++ -c class.cpp

tree.o: tree.cpp class.h tree.h list.h
	g++ -c tree.cpp

list.o: list.cpp class.h tree.h list.h
	g++ -c list.cpp

run: main
	./main

clean:
	rm main main.o class.o tree.o list.o
