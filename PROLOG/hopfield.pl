% add two matrixes(lines)

add_matrixes([], [], []).
add_matrixes(M, [], M).
add_matrixes([], M, M).
add_matrixes([M1|R1], [M2|R2], [M3|R3]) :-
	add_lines(M1, M2, M3),
	add_matrixes(R1, R2, R3).

add_lines([], [], []).
add_lines([], L, L).
add_lines(L, [], L).
add_lines([L1|R1], [L2|R2], [L3|R3]) :-
	L3 is L1 + L2,
	add_lines(R1, R2, R3).

% multiply a matrix(line) with a constant

const_mult_matrix([], _, []).
const_mult_matrix([M1|R1], C, [M2|R2]) :-
	const_mult_line(M1, C, M2),
	const_mult_matrix(R1, C, R2).

const_mult_line([], _, []).
const_mult_line([L1|R1], C, [L2|R2]):-
	L2 is L1 * C,
	const_mult_line(R1, C, R2).
	
% multiply two lines to get a matrix

mult_lines([], [], []).
mult_lines(_, [], []).
mult_lines([], _, []).
mult_lines([L1|R1], L2, [R3|M3]) :-
	const_mult_line(L2, L1, R3),
	mult_lines(R1, L2, M3).

% create an identity matrix with size L

identity_matr(0, []).
identity_matr(L, M5) :-
	append([],[1], M),
	L1 is L-1,
	append_ones(L1, M, M1),
	append([],[M1], M2),
	matr_transp(M2, M3),
	append_zeroes(M3, M4, L1, 0),
	reverse(M4, M5).

% append L "1's" into a list

append_ones(0, M, M).
append_ones(L, M, M2) :-
	L =\= 0,
	append(M, [1], M1),
	L1 is L-1,
	append_ones(L1, M1, M2).	
	
% append "0's" at the front and back of each line of a matrix
% (inspired from "append dummies" from exercise 1)

append_zeroes([], [], _, _).
append_zeroes([FirstLine|RestLines], [NewNewFirstLine|NewRestLines], Front, Back) :-
	append_front(FirstLine, Front, NewFirstLine),
	append_back(NewFirstLine, Back, NewNewFirstLine),
	NewFront is Front-1,
	NewBack is Back+1,
	append_zeroes(RestLines, NewRestLines, NewFront, NewBack).

append_front(List, Front, NewList) :-
	Front =:= 0, NewList = List.
append_front(List, Front, NewNewList) :-
	Front =\= 0,
	append([0], List, NewList),
	NewFront is Front-1,
	append_front(NewList, NewFront, NewNewList).

append_back(List, Back, NewList) :-
	Back =:= 0, NewList = List.
append_back(List, Back, NewNewList) :-
	Back =\= 0,
	append(List, [0],NewList),
	NewBack is Back-1,
	append_back(NewList, NewBack, NewNewList).

del_first([], [], []).
del_first([[X|L]|R], [X|RX], [L|RL]) :-
   del_first(R, RX, RL).

matr_transp(M, []) :-
   empty_lists(M).
matr_transp(M, [C|TM]) :-
   del_first(M, C, RM),
   matr_transp(RM, TM).

empty_lists([]).
empty_lists([[]|M]) :-
   empty_lists(M).

% returns the length of a matrixe's first line

first_line_length([], 0).
first_line_length([M|_], L) :-
	length(M, L).

hopfield1([], X, X).	
hopfield1([M|R], W, W3) :-
	mult_lines(M, M, W1),
	add_matrixes(W, W1, W2),
	hopfield1(R, W2, W3).

hopfield([], []).
hopfield(M, W) :-
	first_line_length(M, L),
	identity_matr(L, I),
	length(M, L1),
	L2 is -1*L1,
	const_mult_matrix(I, L2, I2),
	hopfield1(M, I2, W).



	
	

	

