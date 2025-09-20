# File: makefile

main: main.o object.o string.o plane.o component.o employee.o
	g++ -g -std=c++11 -o main main.o object.o string.o plane.o component.o employee.o

object.o: object.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c object.cpp

string.o: string.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c string.cpp

employee.o: employee.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c employee.cpp

component.o: component.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c component.cpp

plane.o: plane.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c plane.cpp

main.o: main.cpp object.h string.h plane.h component.h employee.h
	g++ -g -std=c++11 -c main.cpp

run: main
	./main

clean:
	rm main main.o object.o string.o plane.o component.o employee.o
