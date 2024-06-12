:- compile(flight_data).

%:-compile(listpr).

:- lib(ic).
:- lib(branch_and_bound).

flights(I, X, Cost) :-
	get_flight_data(I, N, PairingList, CostList),
	length(X, N),
	X #:: [0,1],
	constrain(N, X, PairingList),
	search(X, 0, input_order, indomain, complete, []).

constrain(0, _, _).
constrain(N, X, P) :-
	N #>= 1,
	findall(Pairs, (member(Pairs,P), member(N, P)), NPairs),
	N1 #= N-1,
	constrain(N1, X, P).
	
	
	

	
	
	
	
	