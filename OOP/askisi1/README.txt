File: README

AM: 1115201800003

Name: Adamopoulos Michael

Exercise 1 contains following files:

- class.h
- class.cpp
- main.cpp
- makefile

For compilation use the following commands(2 options):

- make run clean

- g++ -c main.cpp class.cpp
  g++ -o main main.o class.o
  ./main

More details:

- class.h:

	This header file contains the definitions of all the classes used in the exercise.
	There are 3 seperate classes(forum, thread, post), each to represent a different object in the exercise plus a struct(date) to
		represent the date of creation(in days, months and years) of each class as a single entity. Each class is created on
		the same date for the purposes of this exercise.
	All the elements that make up each class are hidden in the private section of the class, in order to not be visible from the outside world.
	On the contrary, the functions that access or alter those elements are defined in the public section.
	The forum class contains an array of pointers to class 'threads', in order to access its threads. Same with thread class and its posts.
	2 constant variables(post_cap and thread_cap) represent the number of posts created per thread and threads per forum and remain unaltered.

- class.cpp:

	The name of the creators/titles/subject and the texts for the classes are randomly generated from some arrays with 'symbolic' names.
	There is a global variable(post_id) which is defined in 'class.cpp' and in 'main.cpp'(as extern), which represents each post's id. It
		starts with the value 1(for the first post) and grows by 1 after a post is created.


