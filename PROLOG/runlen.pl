create_list(X, 1, [X]).
create_list(X, Num, [X|R]):-
	Num1 is Num - 1,
	create_list(X, Num1, R).

decode_rl([], []).
decode_rl([X|R], L):-
	X \= (A,Num),
	append([X], [], L1),
	decode_rl(R, L2),
	append(L1, L2, L).
decode_rl([(X, Num)|R], L):-
	create_list(X, Num, L1),
	decode_rl(R, L2),
	append(L1, L2, L).
	
find_cons_pref([X],[X],[]).
find_cons_pref([X,X|List], [X|Pref], Rest):-
	find_cons_pref([X|List], Pref, Rest).
find_cons_pref([X,Y|List], [X], [Y|List]):-
	X \= Y.

encode_rl([],[]).
encode_rl(List, Encoded):-
	find_cons_pref(List, Pref, Rest),
	convert(Pref, C),
	append(C, Encoded2, Encoded),
	encode_rl(Rest, Encoded2).

convert([],[]).	
convert([X], [X]).
convert([L|R], [(L,X1)]):-
	length(R, X),
	X1 is X+1.

	
	
	
	

	
	
	
	
	